#include "s21_graphwindow.h"

#include "./ui_s21_graphwindow.h"
#include "qcustomplot.h"

extern "C" {
#include "s21_smartcalc.h"
}

GraphWindow::GraphWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::GraphWindow) {
  ui->setupUi(this);
}

GraphWindow::~GraphWindow() { delete ui; }

void GraphWindow::on_to_draw_button_clicked(token* rpn, double x_min,
                                            double x_max) {
  ui->widget->clearGraphs();

  double range_max = 1000000;
  if (x_max > range_max) x_max = range_max;
  if (x_min < -range_max) x_min = -range_max;

  double h = 0.1;
  for (double X = x_min; X < x_max; X += h) {
    x.push_back(X);
    double Y = s21_calculate(rpn, X);
    y.push_back(Y);
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->rescaleAxes();
  ui->widget->replot();

  x.clear();
  y.clear();
}

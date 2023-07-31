#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>

#include "QVector"

extern "C" {
#include "scp_smartcalc.h"
}

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit GraphWindow(QWidget *parent = nullptr);
  void on_to_draw_button_clicked(token *rpn, double x_min, double x_max);

  ~GraphWindow();

 private:
  Ui::GraphWindow *ui;
  //  double xBegin, xEnd, h, X;
  //  int N;
  //  char temp_str[255];
  //  QString text_str;
  QVector<double> x, y;
};

#endif  // GRAPHWINDOW_H

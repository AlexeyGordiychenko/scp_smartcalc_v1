#include <QApplication>

#include "s21_smartcalc_app.h"

int main(int argc, char *argv[]) {
  QLocale::setDefault(QLocale::C);
  QApplication a(argc, argv);
  s21_smartcalc_app w;
  w.show();
  return a.exec();
}

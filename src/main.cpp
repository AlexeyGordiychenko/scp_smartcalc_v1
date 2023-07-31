#include <QApplication>

#include "scp_smartcalc_app.h"

int main(int argc, char *argv[]) {
  QLocale::setDefault(QLocale::C);
  QApplication a(argc, argv);
  scp_smartcalc_app w;
  w.show();
  return a.exec();
}

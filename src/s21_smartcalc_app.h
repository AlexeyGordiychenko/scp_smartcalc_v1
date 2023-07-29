#ifndef S21_SMARTCALC_APP_H
#define S21_SMARTCALC_APP_H

#include <QDoubleValidator>
#include <QLocale>
#include <QMainWindow>

extern "C" {
#include "s21_credit.h"
}
#include "s21_graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class s21_smartcalc_app;
}
QT_END_NAMESPACE

class s21_smartcalc_app : public QMainWindow {
  Q_OBJECT

 public:
  s21_smartcalc_app(QWidget *parent = nullptr);
  ~s21_smartcalc_app();

 private:
  Ui::s21_smartcalc_app *ui;
  GraphWindow *s21_graphWindow;

 private slots:
  void s21_button_to_result();
  void s21_button_to_result_with_bracket();
  void s21_clear_result();
  void s21_set_calc_result_invalid_x();
  void s21_set_calc_result_invalid_exp();
  void s21_calc_result();
  void s21_set_credit_result_invalid();
  void s21_set_credit_result(s21_credit_t res);
  void s21_credit_result();
  QString get_format_string(double value);

 private:
  bool expEvaluated = false;
};

#endif  // S21_SMARTCALC_APP_H

#ifndef SCP_SMARTCALC_APP_H
#define SCP_SMARTCALC_APP_H

#include <QDoubleValidator>
#include <QLocale>
#include <QMainWindow>

extern "C" {
#include "scp_credit.h"
}
#include "scp_graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class scp_smartcalc_app;
}
QT_END_NAMESPACE

class scp_smartcalc_app : public QMainWindow {
  Q_OBJECT

 public:
  scp_smartcalc_app(QWidget *parent = nullptr);
  ~scp_smartcalc_app();

 private:
  Ui::scp_smartcalc_app *ui;
  GraphWindow *scp_graphWindow;

 private slots:
  void scp_button_to_result();
  void scp_button_to_result_with_bracket();
  void scp_clear_result();
  void scp_set_calc_result_invalid_x();
  void scp_set_calc_result_invalid_exp();
  void scp_calc_result();
  void scp_set_credit_result_invalid();
  void scp_set_credit_result(scp_credit_t res);
  void scp_credit_result();
  QString get_format_string(double value);

 private:
  bool expEvaluated = false;
};

#endif  // SCP_SMARTCALC_APP_H

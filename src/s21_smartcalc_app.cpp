#include "s21_smartcalc_app.h"

#include "ui_s21_smartcalc_app.h"

extern "C" {
#include "s21_credit.h"
#include "s21_smartcalc.h"
}

s21_smartcalc_app::s21_smartcalc_app(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::s21_smartcalc_app) {
  ui->setupUi(this);
  s21_graphWindow = new GraphWindow(this);

  // radio buttons

  QObject::connect(ui->calcMode, &QRadioButton::toggled,
                   [this](bool checked) { ui->calcX->setVisible(checked); });
  QObject::connect(ui->graphMode, &QRadioButton::toggled,
                   [this](bool checked) { ui->graphX->setVisible(checked); });
  ui->calcMode->setChecked(true);
  ui->graphMode->setChecked(false);
  ui->credit_annuity->setChecked(true);
  ui->credit_differentiated->setChecked(false);

  // calc buttons

  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result_with_bracket()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(s21_button_to_result()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this,
          SLOT(s21_clear_result()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this,
          SLOT(s21_calc_result()));

  // validation
  QDoubleValidator *x_validator = new QDoubleValidator(
      std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(),
      std::numeric_limits<int>::max(), this);

  x_validator->setNotation(QDoubleValidator::StandardNotation);
  ui->valueX->setValidator(x_validator);
  ui->valueXMax->setValidator(x_validator);
  ui->valueXMin->setValidator(x_validator);

  QDoubleValidator *credit_validator =
      new QDoubleValidator(0, std::numeric_limits<double>::max(),
                           std::numeric_limits<int>::max(), this);
  credit_validator->setNotation(QDoubleValidator::StandardNotation);
  ui->credit_principal->setValidator(credit_validator);
  ui->credit_rate->setValidator(credit_validator);
  ui->credit_term->setValidator(credit_validator);

  // calc button
  connect(ui->credit_calc, SIGNAL(clicked()), this, SLOT(s21_credit_result()));
}

s21_smartcalc_app::~s21_smartcalc_app() { delete ui; }

void s21_smartcalc_app::s21_button_to_result_with_bracket() {
  s21_button_to_result();
  ui->expressionText->setText(ui->expressionText->text() + "(");
}

void s21_smartcalc_app::s21_button_to_result() {
  if (expEvaluated) {
    s21_clear_result();
    expEvaluated = false;
  };
  QPushButton *button = (QPushButton *)sender();

  QString new_label = ui->expressionText->text() + button->text();

  ui->expressionText->setText(new_label);
}

void s21_smartcalc_app::s21_clear_result() { ui->expressionText->setText(""); }

void s21_smartcalc_app::s21_set_calc_result_invalid_x() {
  ui->expressionText->setText("Invalid 'x' value");
}
void s21_smartcalc_app::s21_set_calc_result_invalid_exp() {
  ui->expressionText->setText("Invalid expression");
}

void s21_smartcalc_app::s21_set_credit_result_invalid() {
  ui->credit_monthly->setText("Invalid input");
  ui->credit_over->setText("Invalid input");
  ui->credit_total->setText("Invalid input");
}

QString s21_smartcalc_app::get_format_string(double value) {
  return QString::number(value, 'f', 2);
}

void s21_smartcalc_app::s21_set_credit_result(s21_credit_t res) {
  QString monthly_text = get_format_string(res.monthly_start);
  if (res.monthly_start != res.monthly_end) {
    monthly_text += "...";
    monthly_text += get_format_string(res.monthly_end);
  }
  ui->credit_monthly->setText(monthly_text);
  ui->credit_over->setText(get_format_string(res.over));
  ui->credit_total->setText(get_format_string(res.total));
}

void s21_smartcalc_app::s21_credit_result() {
  bool credit_principal_ok, credit_term_ok, credit_rate_ok;
  double credit_principal =
      ui->credit_principal->text().toDouble(&credit_principal_ok);
  double credit_term = ui->credit_term->text().toDouble(&credit_term_ok);
  double credit_rate = ui->credit_rate->text().toDouble(&credit_rate_ok);
  if (credit_principal_ok && credit_term_ok && credit_rate_ok) {
    s21_credit_t res;
    if (ui->credit_annuity->isChecked()) {
      res = s21_calculate_annuity(credit_principal, credit_term, credit_rate);
    } else {
      res = s21_calculate_differentiated(credit_principal, credit_term,
                                         credit_rate);
    }
    s21_set_credit_result(res);
  } else {
    s21_set_credit_result_invalid();
  }
}
void s21_smartcalc_app::s21_calc_result() {
  QString exp = ui->expressionText->text();
  std::string tmpStr = exp.toStdString();
  const char *c_exp = tmpStr.c_str();

  struct token *rpn = s21_exp_to_rpn(c_exp);
  if (rpn) {
    if (ui->graphMode->isChecked()) {
      bool x_min_ok, x_max_ok;
      double x_value_min = ui->valueXMin->text().toDouble(&x_min_ok);
      double x_value_max = ui->valueXMax->text().toDouble(&x_max_ok);
      if (x_min_ok && x_max_ok) {
        s21_graphWindow->on_to_draw_button_clicked(rpn, x_value_min,
                                                   x_value_max);
        s21_graphWindow->show();
      } else {
        s21_set_calc_result_invalid_x();
      }
    } else {
      double value = 0, x_value = 0;
      bool x_ok = true;
      if (ui->expressionText->text().contains("x")) {
        x_value = ui->valueX->text().toDouble(&x_ok);
      }
      if (x_ok) {
        value = s21_calculate(rpn, x_value);
        QString numberResult = QString::number(value, 'g', 17);
        ui->expressionText->setText(numberResult);
      } else {
        s21_set_calc_result_invalid_x();
      }
    }
    free(rpn);
  } else {
    s21_set_calc_result_invalid_exp();
  }
  expEvaluated = true;
}

#ifndef S21_CREDIT_H
#define S21_CREDIT_H

typedef struct {
  double monthly_start;
  double monthly_end;
  double over;
  double total;
} s21_credit_t;

s21_credit_t s21_calculate_annuity(double principal, double term,
                                   double interestRate);
s21_credit_t s21_calculate_differentiated(double principal, double term,
                                          double interestRate);

#endif  // S21_CREDIT_H
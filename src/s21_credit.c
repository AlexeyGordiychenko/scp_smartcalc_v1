#include "s21_credit.h"

#include <math.h>

static double s21_calculate_differentiated_monthly(double principal,
                                                   double term,
                                                   double interestRate, int m) {
  double i = interestRate / 12 / 100;
  int N = term * 12;
  double principalPayment = principal / N;
  double interestPayment = (principal - (principalPayment) * (m - 1)) * i;
  return principalPayment + interestPayment;
}

s21_credit_t s21_calculate_annuity(double principal, double term,
                                   double interestRate) {
  double r = interestRate / 12 / 100;
  int n = term * 12;
  double monthly =
      round(((principal * r * pow((1 + r), n)) / (pow((1 + r), n) - 1)) * 100) /
      100;
  double total = monthly * term * 12;

  s21_credit_t credit_res = {monthly, monthly, total - principal, total};
  return credit_res;
}

s21_credit_t s21_calculate_differentiated(double principal, double term,
                                          double interestRate) {
  double total = 0;
  int m = 1;
  double monthly_start =
      s21_calculate_differentiated_monthly(principal, term, interestRate, m++);
  total += monthly_start;
  for (; m < term * 12; m++) {
    total +=
        s21_calculate_differentiated_monthly(principal, term, interestRate, m);
  }
  double monthly_end =
      s21_calculate_differentiated_monthly(principal, term, interestRate, m);
  total += monthly_end;
  s21_credit_t credit_res = {monthly_start, monthly_end, total - principal,
                             total};
  return credit_res;
}
#include "scp_credit.h"

#include <math.h>

static double scp_calculate_differentiated_monthly(double principal,
                                                   double term,
                                                   double interestRate, int m) {
  double i = interestRate / 12 / 100;
  int N = term * 12;
  double principalPayment = principal / N;
  double interestPayment = (principal - (principalPayment) * (m - 1)) * i;
  return principalPayment + interestPayment;
}

scp_credit_t scp_calculate_annuity(double principal, double term,
                                   double interestRate) {
  double r = interestRate / 12 / 100;
  int n = term * 12;
  double monthly =
      round(((principal * r * pow((1 + r), n)) / (pow((1 + r), n) - 1)) * 100) /
      100;
  double total = monthly * term * 12;

  scp_credit_t credit_res = {monthly, monthly, total - principal, total};
  return credit_res;
}

scp_credit_t scp_calculate_differentiated(double principal, double term,
                                          double interestRate) {
  double total = 0;
  int m = 1;
  double monthly_start =
      scp_calculate_differentiated_monthly(principal, term, interestRate, m++);
  total += monthly_start;
  for (; m < term * 12; m++) {
    total +=
        scp_calculate_differentiated_monthly(principal, term, interestRate, m);
  }
  double monthly_end =
      scp_calculate_differentiated_monthly(principal, term, interestRate, m);
  total += monthly_end;
  scp_credit_t credit_res = {monthly_start, monthly_end, total - principal,
                             total};
  return credit_res;
}
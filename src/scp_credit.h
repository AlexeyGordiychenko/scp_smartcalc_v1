#ifndef SCP_CREDIT_H
#define SCP_CREDIT_H

typedef struct {
  double monthly_start;
  double monthly_end;
  double over;
  double total;
} scp_credit_t;

scp_credit_t scp_calculate_annuity(double principal, double term,
                                   double interestRate);
scp_credit_t scp_calculate_differentiated(double principal, double term,
                                          double interestRate);

#endif  // SCP_CREDIT_H
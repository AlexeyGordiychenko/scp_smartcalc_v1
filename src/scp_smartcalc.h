#ifndef SCP_SMART_CALC_H
#define SCP_SMART_CALC_H

typedef struct token {
  double value;
  char type;
  struct token* next;
} token;

struct token* scp_exp_to_rpn(const char* exp);
double scp_calculate(struct token* rpn, double x);

#endif  // SCP_SMART_CALC_H

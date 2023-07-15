#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

typedef struct token {
  double value;
  char type;
  struct token* next;
} token;

struct token* s21_exp_to_rpn(char* exp);
double s21_calculate_plain_exp(char* exp, double x);
double s21_calculate(struct token* rpn, double x);

#endif  // S21_SMART_CALC_H

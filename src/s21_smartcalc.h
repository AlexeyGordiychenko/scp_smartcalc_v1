#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

typedef struct token {
  double value;
  char type;
  struct token* next;
} token;

struct token* s21_exp_to_rpn(const char* exp);
double s21_calculate(struct token* rpn, double x);

#endif  // S21_SMART_CALC_H

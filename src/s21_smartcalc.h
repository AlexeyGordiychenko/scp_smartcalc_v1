#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

typedef struct token {
  double value;
  char type;
  struct token* next;
} token;

#endif  // S21_SMART_CALC_H

#ifndef S21_UTILS_H
#define S21_UTILS_H

#include <stdbool.h>

#include "s21_smartcalc.h"

//+-/*^
// unary +-
// mod, cos, sin, tan, acos, asin, atan, sqrt, ln, log
//()
#define MAX_EXP_LEN 255

enum {
  S21_NONE,
  S21_NUMBER,
  S21_X = 120,
  S21_OPEN_PARENTHESIS = 97,  // char 'a'
  S21_CLOSE_PARENTHESIS,
  S21_DIV,
  S21_MUL,
  S21_EXP,
  S21_PLUS,
  S21_MINUS,
  S21_MOD,
  S21_COS,
  S21_SIN,
  S21_TAN,
  S21_ACOS,
  S21_ASIN,
  S21_ATAN,
  S21_SQRT,
  S21_LN,
  S21_LOG  // char 'p'
};

bool s21_is_operator(int type);
bool s21_is_value(int type);
bool s21_is_function(int type);
bool s21_is_unary_operator(int type);
double s21_calculate_unary(double value, char type);
double s21_calculate_binary(double value1, double value2, char type);

#endif  // S21_UTILS_H
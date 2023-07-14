#include "s21_utils.h"

#include <math.h>

bool s21_is_operator(int type) { return type >= S21_DIV && type <= S21_MOD; }

bool s21_is_value(int type) { return type == S21_NUMBER || type == S21_X; }

bool s21_is_function(int type) { return type >= S21_COS; }

bool s21_is_unary_operator(int type) {
  return type == S21_PLUS || type == S21_MINUS;
}

double s21_calculate_unary(double value, char type) {
  double res = 0;
  switch (type) {
    case S21_COS:
      res = cos(value);
      break;
    case S21_SIN:
      res = sin(value);
      break;
    case S21_TAN:
      res = tan(value);
      break;
    case S21_ACOS:
      res = acos(value);
      break;
    case S21_ASIN:
      res = asin(value);
      break;
    case S21_ATAN:
      res = atan(value);
      break;
    case S21_SQRT:
      res = sqrt(value);
      break;
    case S21_LN:
      res = log(value);
      break;
    case S21_LOG:
      res = log10(value);
      break;
  }
  return res;
}

double s21_calculate_binary(double value1, double value2, char type) {
  double res = 0;
  switch (type) {
    case S21_DIV:
      res = value1 / value2;
      break;
    case S21_MUL:
      res = value1 * value2;
      break;
    case S21_EXP:
      res = pow(value1, value2);
      break;
    case S21_PLUS:
      res = value1 + value2;
      break;
    case S21_MINUS:
      res = value1 - value2;
      break;
    case S21_MOD:
      res = fmod(value1, value2);
      break;
  }
  return res;
}

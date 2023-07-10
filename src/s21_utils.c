#include "s21_utils.h"

#include <math.h>

bool s21_is_operator(int type) { return type >= S21_DIV && type <= S21_MOD; }

bool s21_is_value(int type) { return type == S21_NUMBER || type == S21_X; }

bool s21_is_function(int type) { return type >= S21_COS; }

bool s21_is_unary_operator(int type) {
  return type == S21_PLUS || type == S21_MINUS;
}

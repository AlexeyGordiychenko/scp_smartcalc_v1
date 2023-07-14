#include "s21_smartcalc.h"

#include <stdlib.h>
#include <string.h>

#include "s21_rpn.h"
#include "s21_stack.h"
#include "s21_validation.h"

double s21_calculate_plain_exp(char *exp) {
  struct token *rpn = s21_exp_to_rpn(exp);
  double res = s21_calculate(rpn, 0);
  free(rpn);
  return res;
}

double s21_calculate(struct token *rpn, double x) {
  struct token *numbers = calloc(1, sizeof(struct token));
  struct token *p_rpn = rpn;
  char type = S21_NONE;
  while (p_rpn && (type = p_rpn->type) != S21_NONE) {
    if (s21_is_value(type)) {
      s21_push(&numbers, (type == S21_NUMBER) ? p_rpn->value : x, S21_NUMBER);
    } else if (type >= S21_COS) {
      struct token *top = s21_pop(&numbers);
      s21_push(&numbers, s21_calculate_unary(top->value, type), S21_NUMBER);
      free(top);
    } else {
      struct token *top2 = s21_pop(&numbers);
      struct token *top1 = s21_pop(&numbers);
      s21_push(&numbers, s21_calculate_binary(top1->value, top2->value, type),
               S21_NUMBER);
      free(top1);
      free(top2);
    }
    p_rpn++;
  }
  struct token *top = s21_pop(&numbers);
  double res = top->value;
  free(top);
  free(numbers);
  return res;
}

struct token *s21_exp_to_rpn(char *exp) {
  char *exp_validated = malloc(strlen(exp) * 3 + 1);
  int exp_count = s21_validate(exp, &exp_validated);
  struct token *rpn = s21_validated_exp_to_rpn(exp_validated, exp_count);
  free(exp_validated);
  return rpn;
}

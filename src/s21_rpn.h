#ifndef S21_RPN_H
#define S21_RPN_H

#include "s21_stack.h"
#include "s21_utils.h"

int s21_get_priority(char type);
void s21_fill_and_move_token(token** token, double value, char type);
void s21_move_from_stack_to_rpn(token** stack, token** p_rpn);
struct token* s21_validated_exp_to_rpn(char* exp, int exp_count);

#endif  // S21_RPN_H

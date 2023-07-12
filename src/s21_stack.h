#ifndef S21_STACK_H
#define S21_STACK_H

#include "s21_smartcalc.h"

void s21_push(token **root, double value, char type);
token *s21_pop(token **root);
int s21_peek_type(token *root);

#endif  // S21_STACK_H

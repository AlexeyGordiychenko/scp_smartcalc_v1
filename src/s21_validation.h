#ifndef S21_VALIDATION_H
#define S21_VALIDATION_H

#include "s21_utils.h"

int s21_parse_operator_function(char **s);
bool s21_parse_number(char **p, char **out);
void s21_output_token(char **p_out, char ctt, char ptt);
int s21_validate(char *str, char **out);
bool s21_is_token_valid(char ctt, char ptt);

#endif  // S21_VALIDATION_H
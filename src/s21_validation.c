#include "s21_validation.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "s21_utils.h"

int s21_parse_operator_function(char **s) {
  char res = S21_NONE;
  char *op = "/*^+-";
  for (int i = 0; *op && !res; op++, i++) {
    if (**s == *op) {
      res = S21_DIV + i;
      (*s)++;
    }
  }
  if (!res) {
    char *func[] = {"mod",  "cos",  "sin", "tan", "acos", "asin",
                    "atan", "sqrt", "log", "ln",  NULL};
    for (int i = 0; func[i] != NULL && res == S21_NONE; i++) {
      int len = strlen(func[i]);
      if (strncmp(*s, func[i], len) == 0) {
        res = S21_MOD + i;
        (*s) += len;
      }
    }
  }
  return res;
}

bool s21_parse_number(char **p_str, char **p_out) {
  *(*p_out)++ = '#';
  double num = 0;
  int len = 0;
  bool res = sscanf(*p_str, "%le%n", &num, &len);
  res = res && *(*p_str + len - 1) != '.';
  while (res && len-- > 0) {
    *(*p_out)++ = *(*p_str)++;
  }
  return res;
}

void s21_output_token(char **p_out, char ctt, char ptt) {
  bool print = true;
  if (ptt == S21_NONE || ptt == S21_OPEN_PARENTHESIS) {
    // add zero for unary minus -2 -> 0-2
    if (ctt == S21_MINUS) {
      *p_out += sprintf(*p_out, "#0#%c", ctt);
      print = false;
    }
  }
  if (print) {
    *p_out += sprintf(*p_out, "#%c", ctt);
  }
}

int s21_validate(char *str, char **out) {
  int parentheses_count = 0, tokens_count = 0;
  bool res = true;
  char prev_token_type = S21_NONE;
  char *p_out = *out;
  for (char *p_str = str; *p_str != '\0' && res;) {
    char curr_token_type = S21_NONE;
    if (*p_str == '(') {
      parentheses_count++;
      curr_token_type = S21_OPEN_PARENTHESIS;
      p_str++;
    } else if (*p_str == ')') {
      curr_token_type = S21_CLOSE_PARENTHESIS;
      res = --parentheses_count >= 0;
      p_str++;
    } else if isdigit (*p_str) {
      curr_token_type = S21_NUMBER;
      res = s21_parse_number(&p_str, &p_out);
    } else if (*p_str == 'x') {
      curr_token_type = S21_X;
      p_str++;
    } else {
      curr_token_type = s21_parse_operator_function(&p_str);
    }
    res = res && s21_is_token_valid(curr_token_type, prev_token_type);
    if (res && curr_token_type != S21_NUMBER) {
      s21_output_token(&p_out, curr_token_type, prev_token_type);
    }
    prev_token_type = curr_token_type;
    tokens_count++;
  }

  if (!res || parentheses_count || (prev_token_type >= S21_PLUS)) {
    tokens_count = 0;
    **out = '\0';
  } else {
    *p_out = '\0';
  }
  return tokens_count;
}

bool s21_is_token_valid(char ctt, char ptt) {
  bool res = false;
  if (ctt == S21_NONE) {
    res = false;
  } else if (s21_is_value(ctt)) {
    // A number should be preceded by an operator or an opening parenthesis.
    res =
        ptt == S21_NONE || s21_is_operator(ptt) || ptt == S21_OPEN_PARENTHESIS;
  } else if (s21_is_operator(ctt)) {
    // An operator should be preceded by a number or a close parenthesis.
    res = s21_is_value(ptt) || ptt == S21_CLOSE_PARENTHESIS;
    if (!res && s21_is_unary_operator(ctt)) {
      // A unary operator can also be the first char or preceded by an
      // opening parenthesis
      res = ptt == S21_NONE || ptt == S21_OPEN_PARENTHESIS;
    }
  } else if (ctt == S21_OPEN_PARENTHESIS) {
    // An opening parenthesis should be preceded by an operator or another
    // opening parenthesis.
    res = ptt == S21_NONE || s21_is_operator(ptt) || s21_is_function(ptt) ||
          ptt == S21_OPEN_PARENTHESIS;
  } else if (ctt == S21_CLOSE_PARENTHESIS) {
    // A closing parenthesis should be preceded by a number or another
    // closing parenthesis.
    res = s21_is_value(ptt) || ptt == S21_CLOSE_PARENTHESIS;
  } else if (s21_is_function(ctt)) {
    // A function should be preceded by a operator or an open parenthesis.
    res =
        ptt == S21_NONE || s21_is_operator(ptt) || ptt == S21_OPEN_PARENTHESIS;
  }
  return res;
}

#include "s21_smartcalc.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MISC FUNCTIONS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static bool s21_is_operator(int type) {
  return type >= S21_DIV && type <= S21_MOD;
}

static bool s21_is_value(int type) {
  return type == S21_NUMBER || type == S21_X;
}

static bool s21_is_function(int type) { return type >= S21_COS; }

static bool s21_is_unary_operator(int type) {
  return type == S21_PLUS || type == S21_MINUS;
}

static int s21_get_priority(char type) {
  int res = 2;
  if (s21_is_unary_operator(type)) {
    res = 1;
  } else if (s21_is_function(type)) {
    res = 4;
  } else if (type == S21_EXP) {
    res = 3;
  } else if (type == S21_OPEN_PARENTHESIS || type == S21_CLOSE_PARENTHESIS) {
    res = -1;
  } else {
    res = 2;
  }
  return res;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * STACK FUNCTIONS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static void s21_push(struct token **root, double value, char type) {
  struct token *new_token = malloc(sizeof(token));
  new_token->value = value;
  new_token->type = type;
  new_token->next = *root;
  *root = new_token;
}

static token *s21_pop(struct token **root) {
  token *top_token = NULL;
  if (root != NULL) {
    top_token = *root;
    *root = top_token->next;
  }
  return top_token;
}

static int s21_peek_type(token *root) { return root->type; }

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * VALIDATION OF AN EXPRESSION
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static int s21_parse_operator_function(char **s) {
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

static bool s21_parse_number(char **p_str, char **p_out) {
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

static void s21_output_token(char **p_out, char ctt, char ptt) {
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

static bool s21_is_token_valid(char ctt, char ptt) {
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

static int s21_validate(char *str, char **out) {
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * RPN FUNCTIONS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static void print_type(char type, double value) {
  switch (type) {
    case S21_NUMBER:
      printf("%g", value);
      break;
    case S21_X:
      printf("x");
      break;
    case S21_OPEN_PARENTHESIS:
      printf("(");
      break;
    case S21_CLOSE_PARENTHESIS:
      printf(")");
      break;
    case S21_DIV:
      printf("/");
      break;
    case S21_MUL:
      printf("*");
      break;
    case S21_EXP:
      printf("^");
      break;
    case S21_PLUS:
      printf("+");
      break;
    case S21_MINUS:
      printf("-");
      break;
    case S21_MOD:
      printf("mod");
      break;
    case S21_COS:
      printf("cos");
      break;
    case S21_SIN:
      printf("sin");
      break;
    case S21_TAN:
      printf("tan");
      break;
    case S21_ACOS:
      printf("acos");
      break;
    case S21_ASIN:
      printf("asin");
      break;
    case S21_ATAN:
      printf("atan");
      break;
    case S21_SQRT:
      printf("sqrt");
      break;
    case S21_LN:
      printf("ln");
      break;
    case S21_LOG:
      printf("log");
      break;
    default:
      break;
  }
}

static void s21_fill_and_move_token(struct token **token, double value,
                                    char type) {
  (*token)->value = value;
  (*token)->type = type;
  print_type(type, value);
  printf(" ");
  (*token)++;
}

static void s21_move_from_stack_to_rpn(struct token **stack,
                                       struct token **p_rpn) {
  struct token *top = s21_pop(stack);
  if (top) {
    s21_fill_and_move_token(p_rpn, top->value, top->type);
    free(top);
  }
}

static struct token *s21_validated_exp_to_rpn(char *exp, int exp_count) {
  struct token *stack = NULL;
  struct token *rpn = calloc(exp_count + 1, sizeof(struct token));
  struct token *p_rpn = rpn;
  char *exp_token = strtok(exp, "#");
  while (exp_token) {
    // If the token is:
    if (isdigit(*exp_token)) {
      // A number – put it into the output queue
      s21_fill_and_move_token(&p_rpn, atof(exp_token), S21_NUMBER);
    } else if (*exp_token == 'x') {
      // A number – put it into the output queue
      s21_fill_and_move_token(&p_rpn, 0, S21_X);
    } else if (s21_is_function(*exp_token) ||
               *exp_token == S21_OPEN_PARENTHESIS) {
      // A function or a left parenthesis – push it onto the stack
      s21_push(&stack, 0, *exp_token);
    } else if (s21_is_operator(*exp_token) || s21_is_function(*exp_token)) {
      // Operator (O1):
      // While there is an token-operator O2 at the top of the
      // stack, that has greater or equal precedence than O1, pop O2 from the
      // stack into the output queue, push O1 onto the stack
      while (stack &&
             s21_get_priority(stack->type) >= s21_get_priority(*exp_token)) {
        s21_move_from_stack_to_rpn(&stack, &p_rpn);
      }
      s21_push(&stack, 0, *exp_token);
    } else if (*exp_token == S21_CLOSE_PARENTHESIS) {
      // A right parenthesis:
      // While the token at the top of the stack is not a left parenthesis, pop
      // the token-operators from the stack into the output queue.
      // Pop the left parenthesis from the stack and discard it.
      // If there is a function token at the top of the stack, then pop the
      // function from the stack into the output queue

      while (stack && s21_peek_type(stack) != S21_OPEN_PARENTHESIS) {
        s21_move_from_stack_to_rpn(&stack, &p_rpn);
      }
      if (stack) free(s21_pop(&stack));
      if (stack && s21_is_function(s21_peek_type(stack))) {
        s21_move_from_stack_to_rpn(&stack, &p_rpn);
      }
    }
    //
    exp_token = strtok(NULL, "#");
  }

  while (stack) {
    s21_move_from_stack_to_rpn(&stack, &p_rpn);
  }

  return rpn;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * CALCULATION FUNCTIONS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static double s21_calculate_unary(double value, char type) {
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

static double s21_calculate_binary(double value1, double value2, char type) {
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

double s21_calculate_plain_exp(char *exp, double x) {
  struct token *rpn = s21_exp_to_rpn(exp);
  double res = s21_calculate(rpn, x);
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

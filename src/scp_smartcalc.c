#include "scp_smartcalc.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  SCP_NONE,
  SCP_NUMBER,
  SCP_OPEN_PARENTHESIS = 97,  // char 'a'
  SCP_CLOSE_PARENTHESIS,
  SCP_DIV,
  SCP_MUL,
  SCP_EXP,
  SCP_PLUS,
  SCP_MINUS,
  SCP_MOD,
  SCP_COS,
  SCP_SIN,
  SCP_TAN,
  SCP_ACOS,
  SCP_ASIN,
  SCP_ATAN,
  SCP_SQRT,
  SCP_LN,
  SCP_LOG,  // char 'q'
  SCP_X = 120
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MISC FUNCTIONS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static bool scp_is_operator(int type) {
  return type >= SCP_DIV && type <= SCP_MOD;
}

static bool scp_is_value(int type) {
  return type == SCP_NUMBER || type == SCP_X;
}

static bool scp_is_function(int type) {
  return type >= SCP_COS && type < SCP_X;
}

static bool scp_is_unary_operator(int type) {
  return type == SCP_PLUS || type == SCP_MINUS;
}

static int scp_get_priority(char type) {
  int res = 2;
  if (scp_is_unary_operator(type)) {
    res = 1;
  } else if (type == SCP_EXP) {
    res = 3;
  } else if (type == SCP_OPEN_PARENTHESIS || type == SCP_CLOSE_PARENTHESIS) {
    res = -1;
  }
  return res;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * STACK FUNCTIONS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static void scp_push(struct token **root, double value, char type) {
  struct token *new_token = malloc(sizeof(token));
  new_token->value = value;
  new_token->type = type;
  new_token->next = *root;
  *root = new_token;
}

static token *scp_pop(struct token **root) {
  token *top_token = NULL;
  if (root != NULL) {
    top_token = *root;
    *root = top_token->next;
  }
  return top_token;
}

static int scp_peek_type(token *root) { return root->type; }

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * VALIDATION OF AN EXPRESSION
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static int scp_parse_operator_function(const char **s) {
  char res = SCP_NONE;
  char *op = "/*^+-";
  for (int i = 0; *op && !res; op++, i++) {
    if (**s == *op) {
      res = SCP_DIV + i;
      (*s)++;
    }
  }
  if (!res) {
    char *func[] = {"mod",  "cos",  "sin", "tan", "acos", "asin",
                    "atan", "sqrt", "ln",  "log", NULL};
    for (int i = 0; func[i] != NULL && res == SCP_NONE; i++) {
      int len = strlen(func[i]);
      if (strncmp(*s, func[i], len) == 0) {
        res = SCP_MOD + i;
        (*s) += len;
      }
    }
  }
  return res;
}

static bool scp_parse_number(const char **p_str, char **p_out) {
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

static void scp_output_token(char **p_out, int *token_count, char ctt,
                             char ptt) {
  if (ctt == SCP_NUMBER) {
    (*token_count)++;
  } else if ((ptt == SCP_NONE || ptt == SCP_OPEN_PARENTHESIS) &&
             (ctt == SCP_MINUS || ctt == SCP_PLUS)) {
    // add zero for unary minus -2 -> 0-2
    // skip unary plus
    if (ctt == SCP_MINUS) {
      *p_out += sprintf(*p_out, "#0#%c", ctt);
      (*token_count) += 2;
    }
  } else {
    *p_out += sprintf(*p_out, "#%c", ctt);
    (*token_count)++;
  }
}

static bool scp_is_token_valid(char ctt, char ptt) {
  bool res = false;
  if (ctt == SCP_NONE) {
    res = false;
  } else if (scp_is_value(ctt)) {
    // A number should be preceded by an operator or an opening parenthesis.
    res =
        ptt == SCP_NONE || scp_is_operator(ptt) || ptt == SCP_OPEN_PARENTHESIS;
  } else if (scp_is_operator(ctt)) {
    // An operator should be preceded by a number or a close parenthesis.
    res = scp_is_value(ptt) || ptt == SCP_CLOSE_PARENTHESIS;
    if (!res && scp_is_unary_operator(ctt)) {
      // A unary operator can also be the first char or preceded by an
      // opening parenthesis
      res = ptt == SCP_NONE || ptt == SCP_OPEN_PARENTHESIS;
    }
  } else if (ctt == SCP_OPEN_PARENTHESIS) {
    // An opening parenthesis should be preceded by an operator or another
    // opening parenthesis.
    res = ptt == SCP_NONE || scp_is_operator(ptt) || scp_is_function(ptt) ||
          ptt == SCP_OPEN_PARENTHESIS;
  } else if (ctt == SCP_CLOSE_PARENTHESIS) {
    // A closing parenthesis should be preceded by a number or another
    // closing parenthesis.
    res = scp_is_value(ptt) || ptt == SCP_CLOSE_PARENTHESIS;
  } else if (scp_is_function(ctt)) {
    // A function should be preceded by a operator or an open parenthesis.
    res =
        ptt == SCP_NONE || scp_is_operator(ptt) || ptt == SCP_OPEN_PARENTHESIS;
  }
  return res;
}

static int scp_validate(const char *str, char **out) {
  int parentheses_count = 0, tokens_count = 0;
  bool res = true;
  char prev_token_type = SCP_NONE;
  char *p_out = *out;
  for (const char *p_str = str; *p_str != '\0' && res;) {
    char curr_token_type = SCP_NONE;
    if (*p_str == '(') {
      parentheses_count++;
      curr_token_type = SCP_OPEN_PARENTHESIS;
      p_str++;
    } else if (*p_str == ')') {
      curr_token_type = SCP_CLOSE_PARENTHESIS;
      res = --parentheses_count >= 0;
      p_str++;
    } else if isdigit (*p_str) {
      curr_token_type = SCP_NUMBER;
      res = scp_parse_number(&p_str, &p_out);
    } else if (*p_str == 'x') {
      curr_token_type = SCP_X;
      p_str++;
    } else {
      curr_token_type = scp_parse_operator_function(&p_str);
    }
    res = res && scp_is_token_valid(curr_token_type, prev_token_type);
    if (res) {
      scp_output_token(&p_out, &tokens_count, curr_token_type, prev_token_type);
    }
    prev_token_type = curr_token_type;
  }

  if (!res || parentheses_count ||
      (prev_token_type >= SCP_DIV && prev_token_type != SCP_X)) {
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

// static void print_type(char type, double value) {
//   switch (type) {
//     case SCP_NUMBER:
//       printf("%g", value);
//       break;
//     case SCP_X:
//       printf("x");
//       break;
//     case SCP_OPEN_PARENTHESIS:
//       printf("(");
//       break;
//     case SCP_CLOSE_PARENTHESIS:
//       printf(")");
//       break;
//     case SCP_DIV:
//       printf("/");
//       break;
//     case SCP_MUL:
//       printf("*");
//       break;
//     case SCP_EXP:
//       printf("^");
//       break;
//     case SCP_PLUS:
//       printf("+");
//       break;
//     case SCP_MINUS:
//       printf("-");
//       break;
//     case SCP_MOD:
//       printf("mod");
//       break;
//     case SCP_COS:
//       printf("cos");
//       break;
//     case SCP_SIN:
//       printf("sin");
//       break;
//     case SCP_TAN:
//       printf("tan");
//       break;
//     case SCP_ACOS:
//       printf("acos");
//       break;
//     case SCP_ASIN:
//       printf("asin");
//       break;
//     case SCP_ATAN:
//       printf("atan");
//       break;
//     case SCP_SQRT:
//       printf("sqrt");
//       break;
//     case SCP_LN:
//       printf("ln");
//       break;
//     case SCP_LOG:
//       printf("log");
//       break;
//     default:
//       break;
//   }
// }

static void scp_fill_and_move_token(struct token **token, double value,
                                    char type) {
  (*token)->value = value;
  (*token)->type = type;
  // print_type(type, value);
  // printf(" ");
  (*token)++;
}

static void scp_move_from_stack_to_rpn(struct token **stack,
                                       struct token **p_rpn) {
  struct token *top = scp_pop(stack);
  if (top) {
    scp_fill_and_move_token(p_rpn, top->value, top->type);
    free(top);
  }
}

static struct token *scp_validated_exp_to_rpn(char *exp, int exp_count) {
  struct token *stack = NULL;
  struct token *rpn = malloc((exp_count + 1) * sizeof(struct token));
  struct token *p_rpn = rpn;
  char *exp_token = strtok(exp, "#");
  while (exp_token) {
    // If the token is:
    if (isdigit(*exp_token)) {
      // A number – put it into the output queue
      scp_fill_and_move_token(&p_rpn, atof(exp_token), SCP_NUMBER);
    } else if (*exp_token == 'x') {
      // A number – put it into the output queue
      scp_fill_and_move_token(&p_rpn, 0, SCP_X);
    } else if (scp_is_function(*exp_token) ||
               *exp_token == SCP_OPEN_PARENTHESIS) {
      // A function or a left parenthesis – push it onto the stack
      scp_push(&stack, 0, *exp_token);
    } else if (scp_is_operator(*exp_token)) {
      // Operator (O1):
      // While there is an token-operator O2 at the top of the
      // stack, that has greater or equal precedence than O1, pop O2 from the
      // stack into the output queue, push O1 onto the stack
      while (stack &&
             scp_get_priority(stack->type) >= scp_get_priority(*exp_token)) {
        scp_move_from_stack_to_rpn(&stack, &p_rpn);
      }
      scp_push(&stack, 0, *exp_token);
    } else if (*exp_token == SCP_CLOSE_PARENTHESIS) {
      // A right parenthesis:
      // While the token at the top of the stack is not a left parenthesis, pop
      // the token-operators from the stack into the output queue.
      // Pop the left parenthesis from the stack and discard it.
      // If there is a function token at the top of the stack, then pop the
      // function from the stack into the output queue

      while (stack && scp_peek_type(stack) != SCP_OPEN_PARENTHESIS) {
        scp_move_from_stack_to_rpn(&stack, &p_rpn);
      }
      if (stack) free(scp_pop(&stack));
      if (stack && scp_is_function(scp_peek_type(stack))) {
        scp_move_from_stack_to_rpn(&stack, &p_rpn);
      }
    }
    exp_token = strtok(NULL, "#");
  }

  while (stack) {
    scp_move_from_stack_to_rpn(&stack, &p_rpn);
  }
  p_rpn->type = SCP_NONE;
  return rpn;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * CALCULATION FUNCTIONS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static double scp_calculate_unary(double value, char type) {
  double res = 0;
  switch (type) {
    case SCP_COS:
      res = cos(value);
      break;
    case SCP_SIN:
      res = sin(value);
      break;
    case SCP_TAN:
      res = tan(value);
      break;
    case SCP_ACOS:
      res = acos(value);
      break;
    case SCP_ASIN:
      res = asin(value);
      break;
    case SCP_ATAN:
      res = atan(value);
      break;
    case SCP_SQRT:
      res = sqrt(value);
      break;
    case SCP_LN:
      res = log(value);
      break;
    case SCP_LOG:
      res = log10(value);
      break;
  }
  return res;
}

static double scp_calculate_binary(double value1, double value2, char type) {
  double res = 0;
  switch (type) {
    case SCP_DIV:
      res = value1 / value2;
      break;
    case SCP_MUL:
      res = value1 * value2;
      break;
    case SCP_EXP:
      res = pow(value1, value2);
      break;
    case SCP_PLUS:
      res = value1 + value2;
      break;
    case SCP_MINUS:
      res = value1 - value2;
      break;
    case SCP_MOD:
      res = fmod(value1, value2);
      break;
  }
  return res;
}

double scp_calculate(struct token *rpn, double x) {
  struct token *numbers = NULL;
  struct token *p_rpn = rpn;
  char type = SCP_NONE;
  while (p_rpn && (type = p_rpn->type) != SCP_NONE) {
    if (scp_is_value(type)) {
      scp_push(&numbers, (type == SCP_NUMBER) ? p_rpn->value : x, SCP_NUMBER);
    } else if (type >= SCP_COS) {
      struct token *top = scp_pop(&numbers);
      scp_push(&numbers, scp_calculate_unary(top->value, type), SCP_NUMBER);
      free(top);
    } else {
      struct token *top2 = scp_pop(&numbers);
      struct token *top1 = scp_pop(&numbers);
      scp_push(&numbers, scp_calculate_binary(top1->value, top2->value, type),
               SCP_NUMBER);
      free(top1);
      free(top2);
    }
    p_rpn++;
  }
  struct token *top = scp_pop(&numbers);
  double res = top->value;
  free(top);
  return res;
}

struct token *scp_exp_to_rpn(const char *exp) {
  char *exp_validated = malloc(strlen(exp) * 3 + 1);
  int exp_count = scp_validate(exp, &exp_validated);
  struct token *rpn = NULL;
  if (exp_count > 0) {
    rpn = scp_validated_exp_to_rpn(exp_validated, exp_count);
  }
  free(exp_validated);
  return rpn;
}

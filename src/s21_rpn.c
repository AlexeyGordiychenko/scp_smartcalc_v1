#include "s21_rpn.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_type(char type, double value) {
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

int s21_get_priority(char type) {
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

void s21_fill_and_move_token(struct token** token, double value, char type) {
  (*token)->value = value;
  (*token)->type = type;
  print_type(type, value);
  printf(" ");
  (*token)++;
}

void s21_move_from_stack_to_rpn(struct token** stack, struct token** p_rpn) {
  struct token* top = s21_pop(stack);
  if (top) {
    s21_fill_and_move_token(p_rpn, top->value, top->type);
    free(top);
  }
}

struct token* s21_validated_exp_to_rpn(char* exp, int exp_count) {
  //
  struct token* stack = NULL;
  struct token* rpn = calloc(exp_count + 1, sizeof(struct token));
  struct token* p_rpn = rpn;
  char* exp_token = strtok(exp, "#");
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

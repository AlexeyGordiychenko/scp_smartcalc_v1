#include "s21_stack.h"

#include <stdlib.h>

void s21_push(struct token** root, double value, char type) {
  struct token* new_token = malloc(sizeof(token));
  new_token->value = value;
  new_token->type = type;
  new_token->next = *root;
  *root = new_token;
}

token* s21_pop(struct token** root) {
  token* top_token = NULL;
  if (root != NULL) {
    top_token = *root;
    *root = top_token->next;
  }
  return top_token;
}

int s21_peek_type(token* root) { return root->type; }
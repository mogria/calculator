#include "expression.h"
#include <stdlib.h>
#include <assert.h>

INIT_CLASS(expression, expression_construct, expression_destruct);

double expression_result(void *_self) {
  struct expression *self = (struct expression *)_self;
  if(self == NULL) return 0.0;
  size_t x;
  size_t num_args = self->operation->arguments;
  double result;
  double *numbers = malloc(sizeof(double) * num_args);

  for(x = 0; x < num_args; x++) {
    numbers[x] = (self->type[x] & IS_EXPRESSION)
      ? expression_result(&self->content[x].expression)
      : self->content[x].number;
  }

  if(self->operation->arguments > 2) {
    result = operator_calc(self->operation, numbers[0], numbers[1], numbers[2]);
  } else if(self->operation->arguments > 1) {
    result = operator_calc(self->operation, numbers[0], numbers[1]);
  } else {
    result = operator_calc(self->operation, numbers[0]);
  }
  free(numbers);
  return result;
}

void expression_set_expression(void *_self, size_t index, struct expression *expr) {
  struct expression *self = (struct expression *)_self;
  assert(index < SUBEXPRESSIONS_NUM);
  self->content[index].expression = expr;
}

void expression_set_number(void *_self, size_t index, double number) {
  struct expression *self = (struct expression *)_self;
  assert(index < SUBEXPRESSIONS_NUM);
  self->content[index].number = number;
}

size_t expression_next_index(void *_self) {
  struct expression *self = (struct expression *)_self;
  size_t x;
  for(x = 0; x < SUBEXPRESSIONS_NUM && self->type[x] != NO_CONTENT; x++) { }
  return x;
}

unsigned char expression_is_valid(void *_self) {
  struct expression *self = (struct expression *)_self;
  return self->operation->arguments == expression_next_index(self);
}

void expression_construct(void *_self, va_list *args) {
  struct expression *self = (struct expression *)_self;
  self->operation = va_arg(args, struct operator*);
  size_t x;
  for(x = 0; x < SUBEXPRESSIONS_NUM; x++) {
    self->type[x] = NO_CONTENT;
  }
}

void expression_destruct(void *self) {
}

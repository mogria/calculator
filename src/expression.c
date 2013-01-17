#include "expression.h"

INIT_CLASS(expression, expression_construct, expression_destruct);

double expression_result(void *_self) {
  struct expression *self = (struct expression *)_self;
  double number1, number2;

  number1 = (self->is_expression & FIRST_IS_EXPRESSION)
    ? expression_result(&self->content[0].expression)
    : self->content[0].number;

  number2 = (self->is_expression & SECOND_IS_EXPRESSION)
    ? expression_result(&self->content[1].expression)
    : self->content[1].number;

  return self->operation->calc(number1, number2);
}

void expression_construct(void *_self, va_list *args) {
  struct expression *self = (struct expression *)_self;
  self->operation = va_arg(args, struct operator*);
  self->is_expression = va_arg(args, expression_check);

  if(self->is_expression & FIRST_IS_EXPRESSION)  {
    self->content[0].expression = va_arg(args, struct expression*);
  } else {
    self->content[0].number = va_arg(args, double);
  }

  if(self->is_expression & SECOND_IS_EXPRESSION)  {
    self->content[1].expression = va_arg(args, struct expression*);
  } else {
    self->content[1].number = va_arg(args, double);
  }
}

void expression_destruct(void *self) {
}

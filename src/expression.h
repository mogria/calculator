#ifndef CALCULATOR_EXPRESSION_H
#define CALCULATOR_EXPRESSION_H

#include <libobj/libobj.h>
#include "operator.h"

CONSTRUCTOR(expression_construct);
DESTRUCTOR(expression_destruct);

#define SUBEXPRESSIONS_NUM 2

typedef enum {
  NO_CONTENT = 0,
  IS_EXPRESSION = 1,
  IS_NUMBER = 2
} expression_type;

CLASS(expression);
  union {
    struct expression *expression;
    double number;
  } content[SUBEXPRESSIONS_NUM];
  expression_type type[SUBEXPRESSIONS_NUM];
  struct operator *operation;
  double (*result)(void *obj);
END_CLASS;
double expression_result(void *_self);
void expression_set_expression(void *_self, size_t index, struct expression *expr);
void expression_set_number(void *_self, size_t index, double number);
unsigned char expression_is_valid(void *_self);

#endif /* CALCULATOR_EXPRESSION_H */

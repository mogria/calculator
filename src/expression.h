#ifndef CALCULATOR_EXPRESSION_H
#define CALCULATOR_EXPRESSION_H

#include <libobj/libobj.h>
#include "operator.h"

CONSTRUCTOR(expression_construct);
DESTRUCTOR(expression_destruct);

typedef enum {
  FIRST_IS_EXPRESSION = 1,
  SECOND_IS_EXPRESSION = 2,
} expression_check;

CLASS(expression);
  union {
    struct expression *expression;
    double number;
  } content[2];
  struct operator *operation;
  expression_check is_expression;
  double (*result)(void *obj);
END_CLASS(expression, expression_construct, expression_destruct);
double expression_result(void *_self);

#endif /* CALCULATOR_EXPRESSION_H */

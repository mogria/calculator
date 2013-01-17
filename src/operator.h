#ifndef CALCULATOR_OPERATOR_H
#define CALCULATOR_OPERATOR_H

#include <libobj/libobj.h>

CONSTRUCTOR(operator_construct);
DESTRUCTOR(operator_destruct);

CLASS(operator);
 double (*calc)(double, double);
 int priority;
 char sign; 
END_CLASS;

int is_operator(char sign);

#endif /* CALCULATOR_OPERATOR_H */

#include "operator.h"

INIT_CLASS(operator, operator_construct, operator_destruct);

static double myadd(va_list *args) {
  return va_arg(*args, double) + va_arg(*args, double);
}

static double mysub(va_list *args) {
  return va_arg(*args, double) - va_arg(*args, double);
}

static double mymul(va_list *args) {
  return va_arg(*args, double) * va_arg(*args, double);
}

static double mydiv(va_list *args) {
  return va_arg(*args, double) / va_arg(*args, double);
}

static char signs[] = { '+', '-', '*', '/'};
static int priorities[] = { 50, 50, 100, 100 };
static size_t arguments[] = { 2, 2, 2, 2 };
static double (*functions[])(va_list *args) = { myadd, mysub, mymul, mydiv };


int is_operator(char sign) {
  int x;
  for(x = 0; x < sizeof(signs); x++) {
    if(sign == signs[x]) break;
  }
  x++;

  if(x > sizeof(signs)) x = 0;
  return x;
}


double operator_calc(void *_self, ...) {
  struct operator *self = (struct operator *) _self;
  va_list args;
  va_start(args, _self);
  double result = self->calc(&args);
  va_end(args);
  return result;
}

void operator_construct(void *_self, va_list *args) {
  struct operator *self = (struct operator *) _self;
  char sign = va_arg(*args, int);
  int index = is_operator(sign);

  if(index) {
    index--;
    self->sign = signs[index];
    self->priority = priorities[index];
    self->arguments = arguments[index];
    self->calc = functions[index];
  }
}

void operator_destruct(void *self) {

}



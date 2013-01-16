#include "operator.h"

static double myadd(double a, double b) {
  return a + b;
}

static double mysub(double a, double b) {
  return a - b;
}

static double mymul(double a, double b) {
  return a * b;
}

static double mydiv(double a, double b) {
  return a / b;
}

static char signs[] = { '+', '-', '*', '/'};
static int priorities[] = { 50, 50, 100, 100 };
static double (*functions[])(double, double) = { myadd, mysub, mymul, mydiv };


int is_operator(char sign) {
  int x;
  for(x = 0; x < sizeof(signs); x++) {
    if(sign == signs[x]) break;
  }
  x++;

  if(x > sizeof(signs)) x = 0;
  return x;
}

void operator_construct(void *_self, va_list *args) {
  struct operator *self = (struct operator *) _self;
  char sign = va_arg(args, int);
  int index = is_operator(sign);

  if(index) {
    index--;
    self->sign = signs[index];
    self->priority = priorities[index];
    self->calc = functions[index];
  }
}

void operator_destruct(void *self) {

}



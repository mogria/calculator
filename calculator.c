#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 80

typedef struct Expression {
  int zahl1;
  struct Expression *expression1;
  char operator;
  int zahl2;
  struct Expression *expression2;
} Expression;

int main() {
  char Input[MAX_INPUT];
  char Format[20];
  do {
    sprintf ( Format, "%%%is", MAX_INPUT );
    scanf ( Format, Input );
    printf("%s:%s", Format, Input );
  } while ( strlen(Input) != 0 );
  puts ( "bye!" );
  return 0;
}

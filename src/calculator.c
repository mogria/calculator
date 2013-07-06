#include <stdio.h> /* input and output functions */
#include <stdlib.h> /* atoi, etc ... */
#include <string.h> /* string functions */
#include <ctype.h> /* isspace() */
#include "operator.h"
#include "expression.h"

#define MAX_INPUT 255

double parse(char *input, int length) {
  char *end = input + length;
  struct expression *root = NULL;
  struct operator *op = NULL;
  struct expression *current = root;
  struct expression *old = root;
  struct expression *to, *from;
  int characters = 0;
  double number;
  while(*input && input < end) {
    if(isspace(*input)) {
      /* do nothing */
    } else if(is_operator(*input)) {
      op = new(operator, *input);
      old = current;
      current = new(expression);
      if(old->operation->priority < op->priority) {
        to = current;
        from = old;
      } else {
        to = old;
        from = current;
      }
      printf("found operator '%c'\n", *input);
    } else if(sscanf(input, "%lf%n", &number, &characters)) {
      printf("number '%lf length '%i' \n", number, characters);
      input += characters - 1;
    }
    input++;
  }
  return expression_result(root);
}

int main() {
  char input[MAX_INPUT] = {}; /* input of the user */
  short exit = 0;

  puts("calculator 15 by mogria\n");

  /* Generating the format of the input string according to MAX_INPUT */
  do {
    /* printing the shell prompt */
    printf("c15> ");
    fflush(stdout);

    /* reading the input */
    fgets(input, MAX_INPUT, stdin);

    /* only process input if input is not empty */
    if(!(exit = (strncmp(input, "exit", 4) == 0))) {
      printf("=> %lf\n", parse(input, MAX_INPUT));
    }

    memset(input, 0, MAX_INPUT);
    /* end programm if input is empty */
  } while(!exit);

  puts("\nbye.");
  return 0;
}

#include <stdio.h> /* input and output functions */
#include <stdlib.h> /* atoi, etc ... */
#include <string.h> /* string functions */

#define MAX_INPUT 255

Expression *parse(char *input);

int main() {
  char input[MAX_INPUT]; /* input of the user */
  short exit = 0;

  puts("calculator 15 by mogria\n");

  /* Generating the format of the input string according to MAX_INPUT */
  do {
    /* printing the shell prompt */
    printf("c15>");
    fflush(stdout);

    /* reading the input */
    fgets(input, MAX_INPUT, stdin);

    /* only process input if input is not empty */
    if(!(exit = (strncmp(input, "exit", 4) == 0))) {
      printf("=> %f\n", process(input));
    }

    /* end programm if input is empty */
  } while(!exit);

  puts("\nbye.");
  return 0;
}

double parse(char *input) {
  double result = 0;
  return result;
}

#include <stdio.h> // input and output functions
#include <stdlib.h> // atoi, etc ...
#include <string.h> // string functions

#define MAX_INPUT 80

typedef struct Expression {
  int zahl1;
  struct Expression *expression1;
  char operator;
  int zahl2;
  struct Expression *expression2;
} Expression;

float process ( char *Input );

int main() {
  char Input[MAX_INPUT]; // input of the user
  char Format[20]; // format of the input
  short More;

  // Intro
  printf ( "Initializing Calculator 15 ...\n" );

  // Generating the format of the input string according to MAX_INPUT
  sprintf ( Format, "%%%is", MAX_INPUT );

  do {
    // printing the shell prompt
    printf ( "c15> " );

    // reading the input
    scanf ( Format, Input );

    // only process input if Input is not empty
    if ( More = ( strcmp ( Input, "exit" ) != 0 ) ) {
      printf ( "=> %f\n", process ( Input ) );
    }
    printf ( "more: %i \n", More );

    // end programm if input is empty
  } while ( More );

  // bye :D
  puts ( "bye!" );
  return 0;
}

// function which processes the input and returns the result das double
float process ( char *Input ) {
  return atof ( Input );
}

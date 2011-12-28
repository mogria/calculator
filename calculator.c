#include <stdio.h> // input and output functions
#include <stdlib.h> // atoi, etc ...
#include <string.h> // string functions

#define MAX_INPUT 80
#define NUM_OPERATIONS 4

typedef struct Operator {
  char operator;
  float ( *funcp ) ( float, float );
} Operator;

typedef struct Expression {
  float zahl1;
  struct Expression *expression1;
  Operator operator;
  float zahl2;
  struct Expression *expression2;
} Expression;

float process ( char *Input );
float myadd ( float a, float b );
float mysub ( float a, float b );
float mymul ( float a, float b );
float mydiv ( float a, float b );
Expression *parse ( char *Input );
float calc ( Expression *Ausdruck );
void freeExpression ( Expression *Ausdruck );

int main() {
  char Input[MAX_INPUT]; // input of the user
  char Format[20]; // format of the input
  short More;

  // Intro
  printf ( "Initializing Calculator 15 ...\n" );

  // Generating the format of the input string according to MAX_INPUT
  sprintf ( Format, "%%%is", MAX_INPUT - 1 );

  do {
    // printing the shell prompt
    printf ( "c15> " );

    // reading the input
    scanf ( Format, Input );

    // only process input if Input is not empty
    if ( More = ( strcmp ( Input, "exit" ) != 0 ) ) {
      printf ( "=> %f\n", process ( Input ) );
    }

    // end programm if input is empty
  } while ( More );

  // bye :D
  puts ( "bye!" );
  return 0;
}

float myadd ( float a, float b ) {
  return a + b;
}

float mysub ( float a, float b ) {
  return a - b;
}

float mymul ( float a, float b ) {
  return a * b;
}

float mydiv ( float a, float b ) {
  return a / b;
}

int isWhitespace ( char c ) {
  return c == ' ' || c == '\t' || c == ' ' || c == '\n' || c == '\r';
}

Operator *isOperator ( char c ) {
  Operator *operator = NULL;
  static Operator operations[NUM_OPERATIONS] = {
    {'+', myadd},
    {'-', mysub},
    {'*', mymul},
    {'/', mydiv}
  };
  int i;

  for ( i = 0; i < NUM_OPERATIONS && operator == NULL i++ ) {
    if ( operations[i].operator == c ) {
      operator = &operations[i];
    }
  }
  return operator;
}

int *isNumber ( char c ) {
  return c >= 48 && c < 58;
}

float getNumber ( char *c ) {
  return atof ( c );
}

int getNumberLength ( char *c ) {
  int length = 0;
  while ( isNumber ( *c ) || *c == '.' ) {
    length++;
    c++;
  }
  return length;
}

Expression *parse ( char *Input ) {
  unsigned int i;
  
  for ( i = 0; Input[i] != '\0' && Input[i] != ')'; i++ ) {
    if ( Input[i] == '(' ) {
      parse ( Input[i] );
    } else if ( isWhitespace ( Input[i] ) ) {
    } else if ( isOperator ( Input[i] ) ) {
    } else if ( isNumber ( Input[i] ) ) {
      
    }
  }
}

Expression *expression ( int index ) {
  static unsigned int num = 0;
  static Expression *expressions  = NULL;
  Expression *back = NULL;
  if ( index < 0 ) {
    if ( index == -1 ) {
      if ( num == 0 ) {
        // initialize the pointer
        expressions = calloc ( num, sizeof ( Element ) );
      }
      num++;
      // allocate new memory for the new object
      expressions = realloc ( expressions, num * sizeof ( Element ) );
      // set the new allocated memory to 0
      memset ( expressions + ( num - 1 ) * sizeof ( Element ), 0, sizeof ( Element ) );
      back = &expressions[num - 1];
      back.operator = '+';
      back.funcp = myadd;
    } else if ( index = -2 ) {
      free ( expressions );
    }
  } else {
    back = &expressions[index];
  }
  return back;
}

float calc ( Expression *Ausdruck ) {
  float zahl1 = Ausdruck.zahl1;
  float zahl2 = Ausdruck.zahl2;
  if ( Ausdruck.expression1 != NULL ) {
    zahl1 = calc ( Ausdruck.expression1 );
  }

  if ( Ausdruck.expression2 != NULL ) {
    zahl2 = calc ( Ausdruck.expression1 );
  }

  return Ausdruck.operator.funcp ( zahl1, zahl2 );
}

void freeExpression ( Expression *Ausdruck ) {
  expression ( -2 );
}

// function which processes the input and returns the result das double
float process ( char *Input ) {
  return atof ( Input );
}


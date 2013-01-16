#include <stdio.h> // input and output functions
#include <stdlib.h> // atoi, etc ...
#include <string.h> // string functions

#define MAX_INPUT 80
#define NUM_OPERATIONS 4

typedef struct Operator {
  char operator;
  float ( *funcp ) ( float, float );
  int value;
} Operator;

typedef struct Expression {
  float zahl1;
  struct Expression *expression1;
  Operator *operator;
  float zahl2;
  struct Expression *expression2;
} Expression;

float process ( char *Input );
float myadd ( float a, float b );
float mysub ( float a, float b );
float mymul ( float a, float b );
float mydiv ( float a, float b );
Expression *parse ( char *Input );
Expression *getExpression ( int index );
float calc ( Expression *Ausdruck );
void freeExpression ( );
Operator *isOperator ( char c );
int isNumber ( char c );
float getNumber ( char *c );
int getNumberLength ( char *c );

int main() {
  char Input[MAX_INPUT]; // input of the user
  short More;

  // Intro
  printf ( "Initializing Calculator 15 ...\n" );

  // Generating the format of the input string according to MAX_INPUT
  do {
    // printing the shell prompt
    printf ( "c15> " );

    // reading the input
    fgets ( Input, MAX_INPUT, stdin );

    // only process input if Input is not empty
    if ( (More = ( memcmp ( Input, "exit", 4 ) != 0 ) ) ) {
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

Operator *isOperator ( char c ) {
  Operator *operator = NULL;
  static Operator operations[NUM_OPERATIONS] = {
    {'+', myadd, 40},
    {'-', mysub, 40},
    {'*', mymul, 20},
    {'/', mydiv, 20}
  };
  int i;

  for ( i = 0; i < NUM_OPERATIONS && operator == NULL; i++ ) {
    if ( operations[i].operator == c ) {
      operator = &operations[i];
    }
  }
  return operator;
}

int isNumber ( char c ) {
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
  puts ( "parsing .. " );
  unsigned int i;
  short first_number = 1;
  Operator *operator;
  Expression *current_expression = getExpression ( -1 );
  Expression *back_expression = current_expression;
  for ( i = 0; Input[i] != '\0' && Input[i] != ')'; i++ ) {
    if ( Input[i] == '(' ) {
      if ( first_number == 1 ) {
        current_expression->expression1 = parse ( &Input[i + 1] );
        first_number = 0;
      } else {
        current_expression->expression2 = parse ( &Input[i + 1] );
        first_number = 1;
      }
    } else if ( ( operator = isOperator ( Input[i] ) ) != NULL ) {
      if ( first_number == 0 ) {
        current_expression->operator = operator;
      } else {
        Expression *new_expression = getExpression ( -1 );
        new_expression->operator = operator;
        if ( new_expression->operator->value > current_expression->operator->value ) {
          puts ( "new lower " );
          new_expression->expression2 = current_expression;
          back_expression = current_expression = new_expression;
        } else {
          puts ( "new higher " );
          current_expression->expression2 = new_expression;
          new_expression->zahl2 = current_expression->zahl2;
          current_expression->zahl2 = 0;
          current_expression = new_expression;
        }
      }
    } else if ( isNumber ( Input[i] ) ) {
      if ( first_number == 1 ) {
        current_expression->zahl1 = getNumber ( &Input [i] );
        first_number = 0;
      } else {
        current_expression->zahl2 = getNumber ( &Input [i] );
        first_number = 1;
      }
      i += getNumberLength ( & Input[i] ) - 1;
    }
  }
  return back_expression;
}

Expression *getExpression ( int index ) {
  static unsigned int num = 0;
  static Expression *expressions = NULL;
  Expression *back = NULL;
  if ( index < 0 ) {
    if ( index == -1 ) {
      if ( num == 0 ) {
        // initialize the pointer
        expressions = calloc ( num, sizeof ( Expression ) );
        if ( expressions == NULL )  {
          puts ( "calloc: Cannot allocate enougth memory" );
          exit ( 1 );
        }
      }
      num++;
      // allocate new memory for the new object
      expressions = realloc ( expressions, num * sizeof ( Expression ) );
      if ( expressions == NULL ) {
        puts ( "realloc: Cannot allocate enougth memory" );
      }
      // set the new allocated memory to 0
      memset ( expressions + ( num - 1 ) * sizeof ( Expression ), 0, sizeof ( Expression ) );
      back = &expressions[num - 1];
      back->operator = isOperator('+');
      back->expression1 = NULL;
      back->expression2 = NULL;
    } else if ( index == -2 ) {
      free ( expressions );
      num = 0;
    }
  } else {
    back = &expressions[index];
  }
  return back;
}

float calc ( Expression *Ausdruck ) {
  puts ( "calculating " );
  float zahl1 = Ausdruck->zahl1;
  float zahl2 = Ausdruck->zahl2;
  puts ( "  check expression 1 " );
  if ( Ausdruck->expression1 != NULL ) {
    puts ( "  using expression 1 " );
    zahl1 = calc ( Ausdruck->expression1 );
  }

  puts ( "  check expression 2 " );
  if ( Ausdruck->expression2 != NULL ) {
    puts ( "  using expression 2 " );
    zahl2 = calc ( Ausdruck->expression2 );
  }

  puts   ( "  calling function pointer of operator" );
  printf ( "  %f %c %f\n", zahl1, Ausdruck->operator->operator, zahl2 );
  return Ausdruck->operator->funcp ( zahl1, zahl2 );
}

void freeExpression ( ) {
  getExpression ( -2 );
}

// function which processes the input and returns the result das double
float process ( char *Input ) {
  float result = calc ( parse ( Input ) );
  freeExpression ( );
  return result;
}

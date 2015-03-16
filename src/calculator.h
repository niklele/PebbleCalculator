#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <pebble.h>

#define QUERY_MAX_SIZE 20
#define EXPRESSION_MAX_SIZE 20

#define PLUS '+'
#define MINUS '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define PERCENT '%'
#define POINT '.'
#define LPAREN '('
#define RPAREN ')'

#define TYPE_OPERATOR 0
#define TYPE_DIGIT 1
#define TYPE_POINT 2
#define TYPE_OTHER 3

uint8_t charType(char ch);

typedef struct
{
  char ch; // operator or 0 to use value
  float val;
} Token;

// final postfix expression to be computed
typedef struct
{
  Token tokens[EXPRESSION_MAX_SIZE];
  uint8_t size;
} Expression;

// Computes the query provided
double Compute(char *query);

// Convert from infix query to postfix (RPN) expression
void Convert(char *query, Expression *expr);

// circular buffer of chars
typedef struct
{
  char *buff;
  uint8_t curr;
  uint8_t size;
} CircularBuffer;

// Populates the given buffer with all operators
void PopulateOperatorList(CircularBuffer *buffer);

// Populates the given buffer with all digits
void PopulateDigitList(CircularBuffer *buffer);

// Cleans up a circular buffer
void DeleteCircularBuffer(CircularBuffer *buffer);

// Get the current char
char *GetCurr(CircularBuffer *buffer);

// Move curr to next char and return the next char
char *GetNext(CircularBuffer *buffer);

#endif /* CALCULATOR_H */
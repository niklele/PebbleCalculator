#ifndef UTIL_H
#define UTIL_H

#include <pebble.h>

#define EXPRESSION_MAX_SIZE 15

// numbers 0-9 are represented by 0-9
#define PLUS 10
#define MINUS 11
#define MULTIPLY 12
#define DIVIDE 13
#define PERCENT 14
#define POINT 15
#define LPAREN 16
#define RPAREN 17

// Single input. Note: numbers are only single digits.
typedef struct
{
  uint8_t id; // code as defined above
  char ch; // displayed char
} Element;

// Query expression to be computed
typedef struct
{
  Element elems[EXPRESSION_MAX_SIZE];
  uint8_t numElems;
} Expression;

// Add an element to the end of the Expression
// returns false if Expression is full
bool ExpressionAdd(Expression *expr, Element *elem);

// Convert Expression to string for display
char *ToString(Expression *expr);

// Computes the expression provided
double Compute(Expression *expr);

// circular buffer of elements
typedef struct
{
  Element *elems;
  uint8_t currElem;
  uint8_t numElems;
} ElementList;

// Populates the given list with all operators
void PopulateOperatorList(ElementList *list);

// Populates the given list with all digits
void PopulateDigitList(ElementList *list);

// Cleans up an element list
void DeleteElementList(ElementList *list);

// Get the current element
Element *GetCurrElem(ElementList *list);

// Move curr to next element and return the next element
Element *GetNextElem(ElementList *list);

#endif /* UTIL_H */
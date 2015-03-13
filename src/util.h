#ifndef UTIL_H
#define UTIL_H

#include <pebble.h>

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
  Element *elems; // array of elements
} Query;

// circular buffer of elements
typedef struct
{
  Element *elems;
  uint8_t currElem;
  uint8_t numElems;
} ElementList;

#endif /* UTIL_H */
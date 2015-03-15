#include "calculator.h"

double Compute(char *query) {
  Expression expr;
  Convert(query, &expr);
  return 0.0;
}

uint8_t charType(char ch) {
  switch(ch) {
    case PLUS:
    case MINUS:
    case MULTIPLY:
    case DIVIDE:
    case PERCENT:
    case LPAREN:
    case RPAREN:
      return TYPE_OPERATOR;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return TYPE_DIGIT;
    case POINT:
      return TYPE_POINT;
    default:
      return TYPE_OTHER:
  }
}

bool isdigit(char ch) {
  return (charType(ch) == TYPE_DIGIT);
}

double atof(char *s)
{
  double a = 0.0;
  int e = 0;
  int c;
  while ((c = *s++) != '\0' && isdigit(c)) {
    a = a*10.0 + (c - '0');
  }
  if (c == '.') {
    while ((c = *s++) != '\0' && isdigit(c)) {
      a = a*10.0 + (c - '0');
      e = e-1;
    }
  }
  if (c == 'e' || c == 'E') {
    int sign = 1;
    int i = 0;
    c = *s++;
    if (c == '+')
      c = *s++;
    else if (c == '-') {
      c = *s++;
      sign = -1;
    }
    while (isdigit(c)) {
      i = i*10 + (c - '0');
      c = *s++;
    }
    e += i*sign;
  }
  while (e > 0) {
    a *= 10.0;
    e--;
  }
  while (e < 0) {
    a *= 0.1;
    e++;
  }
  return a;
}

void Convert(char *query, Expression *expr) {
// first populate the expression in infix notation, then convert to postfix

  // uint8_t exprIndex = 0;
  Token *curr = expr->tokens;
  uint8_t numStart = 0;
  for (uint8_t i = 0; i < strlen(query); ++i) {
    uint8_t type = charType(query[i]);
    if (type == TYPE_OPERATOR) {
      curr->ch = query[i];
      curr->val = 0;
      curr++;
    } else if (type == TYPE_DIGIT) {
      curr->ch = 0;
      // add based on place and also needs to take decimal point into account
    } else if (type == TYPE_POINT) {

    } else {
      // ignore the character
    }
  }
}

void PopulateOperatorList(CircularBuffer *buffer) {
  buffer->buff = (char *) malloc(8); // NB no null terminator
  buffer->buff[0] = PLUS;
  buffer->buff[1] = MINUS;
  buffer->buff[2] = MULTIPLY;
  buffer->buff[3] = DIVIDE;
  buffer->buff[4] = PERCENT;
  buffer->buff[5] = POINT;
  buffer->buff[6] = LPAREN;
  buffer->buff[7] = RPAREN;
  buffer->size = 8;
  buffer->curr = 0;
}

void PopulateDigitList(CircularBuffer *buffer) {
  buffer->buff = (char *) malloc(10); // NB no null terminator
  buffer->buff[0] = '0';
  buffer->buff[1] = '1';
  buffer->buff[2] = '2';
  buffer->buff[3] = '3';
  buffer->buff[4] = '4';
  buffer->buff[5] = '5';
  buffer->buff[6] = '6';
  buffer->buff[7] = '7';
  buffer->buff[8] = '8';
  buffer->buff[9] = '9';
  buffer->size = 10;
  buffer->curr = 0;
}

void DeleteCircularBuffer(CircularBuffer *buffer) {
  free(buffer->buff);
}

Element *GetCurrElem(CircularBuffer *buffer) {
  return &(buffer->buff[buffer->curr]);
}

Element *GetNextElem(CircularBuffer *buffer) {
  if (buffer->curr == (buffer->size - 1)) {
    buffer->curr = 0;
  } else {
    buffer->curr++;
  }
  return &(buffer->buff[buffer->curr]);
}
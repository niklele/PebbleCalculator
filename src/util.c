#include "util.h"

double Compute(Query *query) {
  return 0.0;
}

void PopulateOperatorList(ElementList *list) {
  Element *elems = (Element *) malloc(16); // TODO check size

  elems[0].id = PLUS;
  elems[0].ch = '+';
  elems[1].id = MINUS;
  elems[1].ch = '-';
  elems[2].id = MULTIPLY;
  elems[2].ch = '*';
  elems[3].id = DIVIDE;
  elems[3].ch = '/';
  elems[4].id = PERCENT;
  elems[4].ch = '%';
  elems[5].id = POINT;
  elems[5].ch = '.';
  elems[6].id = LPAREN;
  elems[6].ch = '(';
  elems[7].id = RPAREN;
  elems[7].ch = ')';

  list->elems = elems;
}

void PopulateNumberList(ElementList *list) {
  Element *elems = (Element *) malloc(20); // TODO check size

  for (int i = 0; i < 10; ++i) {
    elems[i].id = i;
  }
  
  elems[0].ch = '0';
  elems[1].ch = '1';
  elems[2].ch = '2';
  elems[3].ch = '3';
  elems[4].ch = '4';
  elems[5].ch = '5';
  elems[6].ch = '6';
  elems[7].ch = '7';
  elems[8].ch = '8';
  elems[9].ch = '9';


  list->elems = elems;
}

void DeleteElementList(ElementList *list) {
  // cleanup all members
}

Element *GetCurrElem(ElementList *list) {
  return &(list->elems[list->currElem]);
}

Element *GetNextElem(ElementList *list) {
  if (list->currElem == (list->numElems - 1)) {
    list->currElem = 0;
  } else {
    list->currElem++;
  }
  return &(list->elems[list->currElem]);
}
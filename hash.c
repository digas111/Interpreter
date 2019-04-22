#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(char *str) {
  unsigned int res = 0;

  while (*str != '\0') {
    res = res * MULTIPLICADOR + *str;
    str++;
  }
  return res % NHASH;
}

HASHNODE *setdata(HASHNODE *l, union hash data) {
  switch (KIND(l)) {
    case INT_VAR:
      IVALUE(l) = data.ivalue;
      break;
    case FLOAT_VAR:
      FVALUE(l) = data.fvalue;
      break;
    case LABEL:
      LABEL(l) = data.label;
      break;
    default:
      break;
  }

  return l;
}

HASHNODE *new_hashnode(Elem e, union hash data, HASHNODE *next) {
  HASHNODE *l = (HASHNODE *)malloc(sizeof(HASHNODE));

  NAME(l) = ELEMNAME(e);
  NEXT(l) = next;
  KIND(l) = ELEMKIND(e);

  l = setdata(l, data);

  return l;
}

HASHNODE *save(HASHNODE *hashtable[], Elem e, union hash data) {
  unsigned int i = hash(ELEMNAME(e));

  HASHNODE *l = hashtable[i];

  while (l != NULL) {
    if (strcmp(ELEMNAME(e), NAME(l)) == 0) {
      KIND(l) = ELEMKIND(e);
      l = setdata(l, data);
      return *hashtable;
    }

    l = NEXT(l);
  }
  //printf("TOU AQUI\n");

  l = new_hashnode(e, data, hashtable[i]);

  hashtable[i] = l;

  return *hashtable;
}

HASHNODE *get(HASHNODE *hashtable[], Elem e) {
  unsigned int i = hash(ELEMNAME(e));

  HASHNODE *l = hashtable[i];

  while (l != NULL) {
    if (strcmp(ELEMNAME(e), NAME(l)) == 0) {
      return l;
    }

    l = NEXT(l);
  }

  return NULL;
}

void print_hash(HASHNODE *hashtable[]) {
  int i = 0;
  HASHNODE *l;

  for (i = 0; i < NHASH; i++) {
    if ((l = hashtable[i]) != NULL) {
      while (l != NULL) {
        print_hashnode(l);
        l = NEXT(l);
      }
    } else {
      printf("~~\n");
    }
  }
}

void print_hashnode(HASHNODE *l) {
  printf("KIND: %u NAME: %s ", KIND(l), NAME(l));

  switch (KIND(l)) {
    case INT_VAR:  // INT
      printf("VALUE: %d\n", IVALUE(l));
      break;
    case FLOAT_VAR:  // FLOAT
      printf("VALUE: %f\n", FVALUE(l));
      break;
    case LABEL:  // POINTER
      printf("POINTER\n");
      print_instr(l->data.label->instr);
      break;
    default:
      break;
  }
}

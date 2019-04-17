#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

unsigned int hash(char *str) {
  unsigned int res = 0;

  while(*str != '\0'){

    res = res * MULTIPLICADOR + *str;
    str++;

  }
  return res%NHASH;
}

HASHNODE *setdata(HASHNODE *l, union hash data) {

  switch (KIND(l)) {
    case INT:
    IVALUE(l) = data.ivalue;
    case FLOAT:
    FVALUE(l) = data.fvalue;
    case LABELPOINTER:
    LABEL(l) = data.label;
  }

  return l;
}

HASHNODE *new_hashnode(Elkind kind, char *name, union hash data, HASHNODE *next) {

  if (DEBUG) printf("new_hashnode\n");

  HASHNODE *l = (HASHNODE *) malloc (sizeof(HASHNODE));

  NAME(l) = name;
  NEXT(l) = next;
  KIND(l) = kind;

  l = setdata(l,data);

  return l;

}

HASHNODE *save(Elkind kind, char *name, union hash data) {

  unsigned int i = hash(name);

  HASHNODE *l = hashtable[i];

  while (l != NULL) {

    if (strcmp(name,NAME(l))==0) {
      l = setdata(l,data);
      return l;
    }

    l = NEXT(l);
  }

  l = new_hashnode(kind,name,data,hashtable[i]);

  hashtable[i] = l;

  return l;

}

void print() {

  int i=0;
  HASHNODE *l;

  for(i=0; i<NHASH;i++) {
    if ((l = hashtable[i])!=NULL) {
      while(l!=NULL) {
        print_node(l);
        l = NEXT(l);
      }
    }
    else {
      printf("~~\n");
    }
  }

}


void print_node(HASHNODE *l) {

  printf("KIND: %u NAME: %s ", KIND(l), NAME(l));

  switch (KIND(l)) {
    case 0: // INT
    printf("VALUE: %d\n", IVALUE(l));
    break;
    case 1: // FLOAT
    printf("VALUE: %f\n", FVALUE(l));
    break;
    case 2: // POINTER
    printf("POINTER\n");
    break;
  }

}

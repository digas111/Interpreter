#ifndef HASH_H
#define HASH_H
#include "linkedlist.h"

//________________________________________

#define DEBUG 1

//________________________________________

#define NAME(P)((P) -> name)
#define NEXT(P)((P) -> next)
#define IVALUE(P)((P) -> data.ivalue)
#define FVALUE(P)((P) -> data.fvalue)
#define LABEL(P)((P) -> data.label)
#define KIND(P)((P) -> kind)

typedef enum {INT,FLOAT,LABELPOINTER}Elkind;

union hash {
  int ivalue;
  float fvalue;
  NODE *label;
};

typedef struct hashnode {
  Elkind kind;
  char *name;
  struct hashnode *next;
  union hash data;
}HASHNODE;


//________________________________________

#define NHASH 4
#define MULTIPLICADOR 31

HASHNODE *hashtable[NHASH];

//________________________________________

unsigned int hash(char *str);


HASHNODE *setdata(HASHNODE *l,Elkind kind, union hash data);
HASHNODE *new_hashnode(Elkind kind, char *name, union hash data, HASHNODE *next);
HASHNODE *save(Elkind kind,char *name, union hash data);
void print();
void print_node(HASHNODE *l);


//----------------------------------------

#endif

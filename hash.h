#ifndef HASH_H
#define HASH_H
#include "instr.h"
#include "linkedlist.h"

//________________________________________

#define DEBUG 1

//________________________________________

#define NAME(P) ((P)->name)
#define NEXT(P) ((P)->next)
#define IVALUE(P) ((P)->data.ivalue)
#define FVALUE(P) ((P)->data.fvalue)
#define LABEL(P) ((P)->data.label)
#define KIND(P) ((P)->kind)

// typedef enum {INT,FLOAT,LABELPOINTER}Elkind;

union hash {
  int ivalue;
  float fvalue;
  NODE *label;
};

typedef struct hashnode {
  ElemKind kind;
  char *name;
  struct hashnode *next;
  union hash data;
} HASHNODE;

//________________________________________

#define NHASH 4
#define MULTIPLICADOR 31

//________________________________________

unsigned int hash(char *str);

HASHNODE *setdata(HASHNODE *l, union hash data);
HASHNODE *new_hashnode(Elem e, union hash data, HASHNODE *next);
HASHNODE *save(HASHNODE *hashtable[], Elem e, union hash data);
HASHNODE *get(HASHNODE *hashtable[], Elem e);
void print_hash(HASHNODE *hashtable[]);
void print_hashnode(HASHNODE *l);

//----------------------------------------

#endif

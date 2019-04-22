#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "instr.h"

#define INSTR(P) ((P)->instr)
#define NXT(P) ((P)->nxt)

typedef struct node {
  Instr instr;
  struct node *nxt;
} NODE;


NODE *new_node(Instr instr);
NODE *add_last(NODE *lista_instr, Instr i);
void print_llist();
NODE *last(NODE *lista_instr);
int length();

#endif

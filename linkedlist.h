#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "instr.h"

typedef struct node{
    Instr *instr;
    struct node *nxt;
}NODE;

#define INSTR(P)((P)->instr)
#define NXT(P)((P)->nxt)

extern NODE *lista_instr;


NODE *new_node(Instr *instr);
NODE *add_last(Instr *i, NODE *list);
void print_llist(NODE *list);
int length(NODE *list);

#endif

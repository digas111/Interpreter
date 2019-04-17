#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "instr.h"

#define INSTR(P)((P)->instr)
#define NXT(P)((P)->nxt)

typedef struct node{
    Instr *instr;
    struct node *nxt;
}NODE;

extern NODE *lista_instr;

NODE *new_node(Instr *instr);
NODE *add_last(Instr *i);
void print_lista();
int length();

#endif

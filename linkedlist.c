#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

NODE *new_node(Instr i) {
  NODE *l = (NODE *)malloc(sizeof(NODE));
  l->instr = i;
  l->nxt = NULL;
  return l;
}

NODE *add_last(NODE *lista_instr, Instr i) {

  NODE *prev = NULL;
  NODE *curr = lista_instr;
  if (lista_instr == NULL) {
    return new_node(i);
  }
  while (curr != NULL) {
    prev = curr;
    curr = NXT(curr);
  }

  NXT(prev) = new_node(i);

  return lista_instr;
}

NODE *last(NODE *lista_instr) {
  while (NXT(lista_instr) != NULL) {
    lista_instr = NXT(lista_instr);
  }

  return lista_instr;
}

void print_llist(NODE *lista_instr) {

  NODE *curr = lista_instr;
  if (curr == NULL) printf("Lista vazia\n");
  while (curr != NULL) {
    print_instr(curr->instr);
    curr = NXT(curr);
  }

}


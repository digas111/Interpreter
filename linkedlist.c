#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

NODE *lista_instr;

NODE *new_node(Instr *i) {
    NODE *l = (NODE*)malloc(sizeof(NODE));
    l->instr = i;
    l->nxt = NULL;
    return l;
}

NODE *add_last(Instr *i) {
    NODE *prev = NULL;
    NODE *curr = lista_instr;
    if(lista_instr==NULL)
    return new_node(i);
    while(curr!=NULL){
    prev = curr;
    curr = NXT(curr);
    }
    NXT(prev) = new_node(i);
    return lista_instr;
}

void print_llist() {
  NODE *curr = lista_instr;
  if(curr==NULL) printf("Lista vazia\n");
  while(curr!=NULL){
    print_instr(lista_instr->instr);
  curr = NXT(curr);
  }
}

int length(){
    if(lista_instr==NULL) return 0;
    return 1+length(NXT(lista_instr));
}

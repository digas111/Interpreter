#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

NODE *lista_instr;

NODE *new_node(Instr i) {
  NODE *l = (NODE*)malloc(sizeof(NODE));
  l->instr = i;
  l->nxt = NULL;
  return l;
}

void add_last(Instr i) {
  printf("add_last name: !%s!\n", i.elem1.contents.name);
  print_instr(i);

  NODE *prev = NULL;
  NODE *curr = lista_instr;
  if(lista_instr==NULL) {
    printf("is null\n");
    lista_instr = new_node(i);
    return;
  }
  while(curr!=NULL){
    prev = curr;
    curr = NXT(curr);
  }
  NXT(prev) = new_node(i);
  printf("exit add_last\n");
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

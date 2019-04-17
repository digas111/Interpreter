#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

NODE *lista_instr;

NODE *new_node(Instr *i){
    NODE *l = (NODE*)malloc(sizeof(NODE));
    l->instr = i;
    l->nxt = NULL;
    return l;
}

NODE *add_last(Instr *i, NODE *list){
    NODE *prev = NULL;
    NODE *curr = list;
    if(list==NULL)
    return new_node(i);
    while(curr!=NULL){
    prev = curr;
    curr = NXT(curr);
    }
    NXT(prev) = new_node(i);
    return list;
}

void print_llist(NODE *list){
  NODE *curr = list;
  if(curr==NULL) printf("Lista vazia\n");
  while(curr!=NULL){
    print_instr(list->instr);
  curr = NXT(curr);
  }
}

int length(NODE *list){
    if(list==NULL) return 0;
    return 1+length(NXT(list));
}

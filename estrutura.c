#include <stdio.h>
#include <stdlib.h>
#include "lists.h"



//////////////////////////////////////////////////////////////
//                        FUNCOES                           //
//                      LinkedList                          //
//////////////////////////////////////////////////////////////

NODE *new_node(Instr *instruction, NODE *prox){
  NODE *l=(NODE*)malloc(sizeof(NODE));
  //*l é do tipo NODE e l é do tipo NODE*
  //(*l).value = v;
  l->instr = instruction;
  l->nxt = prox;
  return l;
}

int length(NODE *l){
  int len=0;
  while(l!=NULL){
    len++;
    l = NXT(l);
  }
  return len;
}

//retorna o apontador para o nó que  tem x(1ªocorrência)
/*NODE *search(Instr instruction, NODE *l){
  while(l!=NULL && VALUE(l)!=x){
    l=NXT(l);
    return l;
  }
}*/

// coloca novo nó no fim da lista
NODE *add_last(Instr *instruction, NODE *l){
  NODE *prev = NULL;
  NODE *curr = l
  if(l==NULL)
    return new_node(instruction, l);
  while(curr!=NULL){
    prev = curr;
    curr = NXT(curr);
  }
  NXT(prev) = new_node(instruction,NULL);
  return l;
}

//////////////////////////////////////////////////////////////
//                        FUNCOES                           //
//                       Instrucoes                         //
//////////////////////////////////////////////////////////////

Instr *new_instr(Opkind operator, Elem first1, Elem second2, Elem third3){
  Instr *i = (Instr*)malloc(sizeof(Instr));
  i->op = operator;
  i->first = first1;
  i->second = second2;
  i->third = third3;
  return i;
}


//////////////////////////////////////////////////////////////
//                        FUNCOES                           //
//                        Element                           //
//////////////////////////////////////////////////////////////

Elem *new_elem_int(Elemkind k, int v, char *n){
  Elem *e=(Elem*)malloc(sizeof(Elem));
  e->kind = k;
  e->val = v;
  e->name = n;
}

Elem *new_elem_string(Elemkind k, char *c, char *n){
  Elem *e=(Elem*)malloc(sizeof(Elem));
  e->kind = k;
  e->content = c;
  e->name = n;
}


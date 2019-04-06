#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"



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
  NODE *curr = l;
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

Instr *new_instr(OpKind op, Elem *first, Elem *second, Elem *third){
  Instr *i = (Instr*)malloc(sizeof(Instr));
  i->op = op;
  i->first = first;
  i->second = second;
  i->third = third;
  return i;
}

Instr *instrfy(char *linha){
  char *ret = NULL;
  int i;
  //ciclo pra encontrar a needle
  for(i=0; i<SIZEKEYW; i++){
    //ret = strstr(haystack, needle);
    ret = strstr(linha, keywords[i]);
    if(ret != NULL) break;
  }
    switch(i) {
      case 0:
        char *varname = NULL;
        char *str = "(";
        varname = strtok(linha, str);
        str = ")";
        varname = strtok(NULL, str);
        int input;
        scanf("%d", &input);
        Elem *e= new_elem_int(INT_CONST, input, varname);
        Instr *i = new_instr(READ, e, NULL, NULL);
        lista_instr = new_node(i, lista_instr);
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      default:
    }


}


//////////////////////////////////////////////////////////////
//                        FUNCOES                           //
//                        Element                           //
//////////////////////////////////////////////////////////////

Elem *new_elem_int(ElemKind k, int v, char *n){
  Elem *e=(Elem*)malloc(sizeof(Elem));
  e->kind = k;
  e->contents.inte.val = v;
  e->contents.inte.name = n;

  return e;
}

Elem *new_elem_string(ElemKind k, char *c, char *n){
  Elem *e=(Elem*)malloc(sizeof(Elem));
  e->kind = k;
  e->contents.string.content = c;
  e->contents.string.name = n;

  return e;
}


// void run_program(NODE *lista) {
//
//
//
// }

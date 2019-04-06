#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

//VARIAVEIS GLOBAIS

char *keywords[] = {"-ler(", "-if", "-escrever(", "-goto", "-label", "-quit"};
NODE *lista_instr = NULL;


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
      case 0: //ler(_);
        char str[25];
        strcpy(str, linha);
        char *varname = NULL;
        varname = strtok(str, "(");
        varname = strtok(NULL, ")");
        Elem *e= new_elem_int(EMPTY, NULL, varname);
        Instr *i = new_instr(READ, e, NULL, NULL);
        lista_instr = new_node(i, lista_instr);
        break;
      case 1: //if _ goto _
        char str[80];
        strcpy(str, linha);
        char *token1, *token2;
        token1 = strchr(str, ' '); //token1 = (condition) goto LX
        token2 = strtok(token1, "goto"); // token2 = (condition)
        Elem *condition = new_elem_string(CONDITION, token2, NULL);
        strcpy(str, linha);
        token1 = strtok(str, "goto"); //token1 = if (condition)
        token1 = strtok(NULL, " "); //token1 = oto
        token1 = strtok(NULL, " "); //token1 = LX
        Elem *label = new_elem_int(LABEL, NULL, token1);
        Instr *i = new_instr(IF_I, condition, label, NULL);
        lista_instr = new_node(i, lista_instr);
        break;
      case 2: //escrever(_);
        char *linha = "-escrever( p );";
        char str[20];
        strcpy(str, linha);
        char *varname = strtok(str, "(");
        varname = strtok(NULL, ")");
        Elem *e = new_elem_int(EMPTY, NULL, varname);
        Instr *i = new_instr(PRINT, e, NULL, NULL);
        lista_instr = new_node(i, lista_instr);
        break;
      case 3: //goto _
        strcpy(str, linha);
        char *token;
        token =strchr(str, ' ');
        token = strtok(token, "-");
        Elem *e = new_elem_int(LABEL, NULL, token);
        Instr *i = new_instr(GOTO_I, e, NULL, NULL);
        lista_instr = new_node(i, lista_instr);
        break;
      case 4: //label
      char str[25];
        strcpy(str, linha);
        char *token;
        token =strchr(str, ' ');
        token = strtok(token, "-");
        Elem *e = new_elem_int(LABEL, NULL, token);
        Instr *i = new_instr(LABEL_I, e, NULL, NULL);
        lista_instr = new_node(i, lista_instr);
        break;
      case 5: //"-quit"
        char str[25];
        strcpy(str, linha);
        char *token;
        token =strchr(str, '-');
        token = strtok(token, "-");
        Elem *e = new_elem_int(QUIT, NULL, token);
        Instr *i= new_instr(QUIT_I, e, NULL, NULL);
        lista_instr = new_node(i, lista_instr);
        break;
      default: // ATRIB

    }


}


//////////////////////////////////////////////////////////////
//                        FUNCOES                           //
//                        Element                           //
//////////////////////////////////////////////////////////////

Elem *new_elem_int(ElemKind k, int *v, char *n){
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
//
// void exec_instr(Instr command) {
//
//   if ()
//
// }

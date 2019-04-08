#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estrutura.h"

#define SIZEKEYW 10

#define DEBUG 1

//VARIAVEIS GLOBAIS

char *keywords[] = {".ler(", ".if", ".escrever(", ".goto", ".label", ".quit", "+", "-", "*", "/"};
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

// void print (NODE *no) {
//
//   while (no != NULL) {
//
//     printf("%u", no->instr->op);
//
//   }
//
// }

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

void instrfy(char *linha) {
  Elem *e = NULL, *e2 = NULL, *e3 = NULL;
  Instr *in = NULL;
  char *ret = NULL, *token = NULL;
  char str[30], maybe[2];
  int i;
  //ciclo pra encontrar a needle
  for(i=0; i<SIZEKEYW; i++){
    //ret = strstr(haystack, needle);
    ret = strstr(linha, keywords[i]);
    if(ret != NULL) break;
  }


  //////////////////

  strcpy(str, linha);

  //////////////////

  printf("pre switch\n");

  switch(i) {
    case 0: //ler(_);
      if (DEBUG) printf("case 0\n");
      char *varname = NULL;
      strtok(str, "(");
      varname = strtok(NULL, ")");
      if (DEBUG) printf("|%s|\n", varname);
      e = new_elem(EMPTY, varname);
      in = new_instr(READ, e, NULL, NULL);
      lista_instr = new_node(in, lista_instr);
      break;
    case 1: //if _ goto _
      if (DEBUG) printf("case 1\n");

      //token1 = strchr(str, ' '); //token1 = (condition) goto LX
      strtok(str, " ");
      //if (DEBUG) printf("|%s|\n", token1);
      token = strtok(NULL, " goto "); // token2 = (condition)
      if (DEBUG) printf("|%s|\n", token);

      Elem *condition = new_elem_string(CONDITION, token, NULL);

      strtok(NULL," ");
      token = strtok(NULL,"\0");
      if (DEBUG) printf("|%s|\n", token);

      Elem *label = new_elem(LABEL, token);
      in = new_instr(IF_I, condition, label, NULL);
      lista_instr = new_node(in, lista_instr);
      break;
    case 2: //escrever(_);
      if (DEBUG) printf("case 2\n");
      strtok(str, "(");
      varname = strtok(NULL, ")");
      e = new_elem(EMPTY, varname);
      in = new_instr(PRINT, e, NULL, NULL);
      lista_instr = new_node(in, lista_instr);
      break;
    case 3: //goto _
      if (DEBUG) printf("case 3\n");
      strtok(str, " ");
      token = strtok(token, "\0");
      if (DEBUG) printf("|%s|\n",token);
      e = new_elem(LABEL, token);
      in = new_instr(GOTO_I, e, NULL, NULL);
      lista_instr = new_node(in, lista_instr);
      break;
    case 4: //label
      if (DEBUG) printf("case 4\n");
      strtok(str, " ");
      token = strtok(token, "\0");
      e = new_elem(LABEL, token);
      in = new_instr(LABEL_I, e, NULL, NULL);
      lista_instr = new_node(in, lista_instr);
      break;
    case 5: //"-quit"
      if (DEBUG) printf("case 5\n");
      e = new_elem(QUIT, NULL);
      in = new_instr(QUIT_I,NULL,NULL,NULL);
      lista_instr = new_node(in, lista_instr);
      break;
    case 6: //"+"
      if (DEBUG) printf("case 6\n");

      token = strtok(str, ".");
      if (DEBUG) printf("%s\n",token);
      token = strtok(token, "=");
      if (DEBUG) printf("%s\n",token);
      e = new_elem(EMPTY, token);
      token = strtok(NULL, "+");
      if (DEBUG) printf("%s\n",token);
      strcpy(maybe, token);
      if(isdigit(maybe[0])){
        e2 = new_elem_int(INT_CONST, atoi(token), token);
      }
      else {
        e2 = new_elem(EMPTY, token);
      }
      token = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token);
      strcpy(maybe, token);
      if(isdigit(maybe[0])){
        e3 = new_elem_int(INT_CONST, atoi(token), token);
      }
      else {
        e3 = new_elem(EMPTY, token);
      }
      in = new_instr(ADD, e, e2, e3);
      lista_instr = new_node(in, lista_instr);
      break;
    case 7: //"-"
      if (DEBUG) printf("case 7\n");
      token = strtok(str, ".");
      if (DEBUG) printf("%s\n",token);
      token = strtok(token, "=");
      if (DEBUG) printf("%s\n",token);
      e = new_elem(EMPTY, token);
      token = strtok(NULL, "-");
      if (DEBUG) printf("%s\n",token);
      strcpy(maybe, token);
      if(isdigit(maybe[0])){
        e2 = new_elem_int(INT_CONST, atoi(token), token);
      }
      else {
        e2 = new_elem(EMPTY, token);
      }
      token = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token);
      strcpy(maybe, token);
      if(isdigit(maybe[0])){
        e3 = new_elem_int(INT_CONST, atoi(token), token);
      }
      else {
        e3 = new_elem(EMPTY, token);
      }
      in = new_instr(SUB, e, e2, e3);
      lista_instr = new_node(in, lista_instr);
      break;
    case 8:
      if (DEBUG) printf("case 8\n");
      token = strtok(str, ".");
      if (DEBUG) printf("%s\n",token);
      token = strtok(token, "=");
      if (DEBUG) printf("%s\n",token);
      e = new_elem(EMPTY, token);
      token = strtok(NULL, "*");
      if (DEBUG) printf("%s\n",token);
      strcpy(maybe, token);
      if(isdigit(maybe[0])){
        e2 = new_elem_int(INT_CONST, atoi(token), token);
      }
      else {
        e2 = new_elem(EMPTY, token);
      }
      token = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token);
      strcpy(maybe, token);
      if(isdigit(maybe[0])){
        e3 = new_elem_int(INT_CONST, atoi(token), token);
      }
      else {
        e3 = new_elem(EMPTY, token);
      }
      in = new_instr(MUL, e, e2, e3);
      lista_instr = new_node(in, lista_instr);
      break;
    case 9:
    if (DEBUG) printf("case 9\n");
    token = strtok(str, ".");
    if (DEBUG) printf("%s\n",token);
    token = strtok(token, "=");
    if (DEBUG) printf("%s\n",token);
    e = new_elem(EMPTY, token);
    token = strtok(NULL, "/");
    if (DEBUG) printf("%s\n",token);
    strcpy(maybe, token);
    if(isdigit(maybe[0])){
      e2 = new_elem_int(INT_CONST, atoi(token), token);
    }
    else {
      e2 = new_elem(EMPTY, token);
    }
    token = strtok(NULL, "\0");
    if (DEBUG) printf("%s\n",token);
    strcpy(maybe, token);
    if(isdigit(maybe[0])){
      e3 = new_elem_int(INT_CONST, atoi(token), token);
    }
    else {
      e3 = new_elem(EMPTY, token);
    }
    in = new_instr(DIV, e, e2, e3);
    lista_instr = new_node(in, lista_instr);
    break;
    case 10: // ATRIB
      if (DEBUG)  printf("case default\n");
      token = strtok(str, ".");
      token = strtok(token, "=");
      if (DEBUG) printf("%s\n",token);
      e = new_elem(EMPTY, token);
      token = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token);
      strcpy(maybe, token);
      if(isdigit(maybe[0])){
        e2 = new_elem_int(INT_CONST, atoi(token), token);
      }
      else
      e2 = new_elem(EMPTY, token);
      in = new_instr(ATRIB, e, e2, NULL);
      lista_instr = new_node(in, lista_instr);
      break;
    default:
      printf("ERRO\n");
      return;
  }


}


//////////////////////////////////////////////////////////////
//                        FUNCOES                           //
//                        Element                           //
//////////////////////////////////////////////////////////////

Elem *new_elem(ElemKind k, char *n){
  Elem *e=(Elem*)malloc(sizeof(Elem));
  e->kind = k;
  e->contents.inte.name = n;

  return e;
}

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
//
// void exec_instr(Instr command) {
//
//   if ()
//
// }

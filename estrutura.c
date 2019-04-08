#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estrutura.h"

#define SIZEKEYW 10

#define DEBUG 1

//VARIAVEIS GLOBAIS

char *keywords[] = {".ler(", ".if", ".escrever(", ".goto", ".label", ".quit", "+", "-", "*", "/"};

//////////////////////////////////////////////////////////////
//                        FUNCOES                           //
//                      LinkedList                          //
//////////////////////////////////////////////////////////////

NODE *new_node(Instr *instruction) {

  Instr *instr = instruction;

  printf("new_node\n");
  printf("OpKind = %d\n", instr->op);
  printf("First.name: _%s_\n",instr->first->contents.inte.name);
  printf("Second.name: _%s_\n",instr->second->contents.inte.name);
  printf("Third.name: _%s_\n\n",instr->third->contents.inte.name);

  NODE *l=(NODE*)malloc(sizeof(NODE));
  l->instr = instruction;
  l->nxt = NULL;

  //printf("***%s***\n", l->instr->first->contents.inte.name);
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

NODE *add_last(Instr *instruction, NODE *l) {

  Instr *instr = instruction;

  printf("aqui\n");
  printf("OpKind = %d\n", instr->op);
  printf("First.name: _%s_\n",instr->first->contents.inte.name);
  printf("Second.name: _%s_\n",instr->second->contents.inte.name);
  printf("Third.name: _%s_\n\n",instr->third->contents.inte.name);


  NODE*prev = NULL, *curr=l;
  while(curr != NULL) {
    prev = curr;
    curr = NXT(curr);
  }

  if (prev == NULL) return new_node(instr);
  NXT(prev) = new_node(instr);
  return l;
}


void print_lista(NODE *lista){
  NODE *curr = lista;
  if(curr==NULL) printf("Lista vazia\n");
  while(curr!=NULL){
    printf("---------------------------\nOpKind = %d First.name: %s Second.name: %s Third.name: %s\n----------------------------\n", curr->instr->op, curr->instr->first->contents.inte.name, curr->instr->second->contents.inte.name, curr->instr->third->contents.inte.name);
  curr = NXT(curr);
  }
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

Instr *instrfy(char *linha) {
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

  if (DEBUG) printf("pre switch\n");

  switch(i) {
    case 0: //ler(_);
      if (DEBUG) printf("case 0\n");
      char *varname = NULL;
      strtok(str, "(");
      varname = strtok(NULL, ")");
      if (DEBUG) printf("|%s|\n", varname);
      e = new_elem(EMPTY, varname);
      in = new_instr(READ, e, NULL, NULL);
      break;
    case 1: //if _ goto _
      if (DEBUG) printf("case 1\n");
      strtok(str, " ");
      token = strtok(NULL, " goto "); // token2 = (condition)
      if (DEBUG) printf("|%s|\n", token);
      Elem *condition = new_elem_string(CONDITION, token, NULL);
      strtok(NULL," ");
      token = strtok(NULL,"\0");
      if (DEBUG) printf("|%s|\n", token);
      Elem *label = new_elem(LABEL, token);
      in = new_instr(IF_I, condition, label, NULL);
      break;
    case 2: //escrever(_);
      if (DEBUG) printf("case 2\n");
      strtok(str, "(");
      varname = strtok(NULL, ")");
      e = new_elem(EMPTY, varname);
      in = new_instr(PRINT, e, NULL, NULL);
      break;
    case 3: //goto _
      if (DEBUG) printf("case 3\n");
      strtok(str, " ");
      token = strtok(token, "\0");
      if (DEBUG) printf("|%s|\n",token);
      e = new_elem(LABEL, token);
      in = new_instr(GOTO_I, e, NULL, NULL);
      break;
    case 4: //label
      if (DEBUG) printf("case 4\n");
      strtok(str, " ");
      token = strtok(token, "\0");
      e = new_elem(LABEL, token);
      in = new_instr(LABEL_I, e, NULL, NULL);
      break;
    case 5: //"-quit"
      if (DEBUG) printf("case 5\n");
      e = new_elem(QUIT, NULL);
      in = new_instr(QUIT_I,NULL,NULL,NULL);
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
      break;
    case 10: // ATRIB
      if (DEBUG) printf("case default\n");
      token = strtok(str, ".");
      token = strtok(token, "=");
      if (DEBUG) printf("-%s-\n",token);
      e = new_elem(EMPTY, token);
      token = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token);
      strcpy(maybe, token);
      if(isdigit(maybe[0])){
        e2 = new_elem_int(INT_CONST, atoi(token), token);
      }
      else
      e2 = new_elem(EMPTY, token);
      e3 = new_elem_empty();
      in = new_instr(ATRIB, e, e2, e3);
      break;
    default:
      printf("ERRO\n");
      exit(EXIT_FAILURE);
  }

  printf("____________________________\n");
  printf("in\n");
  printf("OpKind = %d\n", in->op);
  printf("First.name: _%s_\n",in->first->contents.inte.name);
  printf("Second.name: _%s_\n",in->second->contents.inte.name);
  printf("Third.name: _%s_\n\n",in->third->contents.inte.name);
  printf("____________________________\n");

  return in;

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

Elem *new_elem_empty(){
    Elem *e= new_elem(EMPTY,NULL);
  return e;
}


void run_program(NODE *lista) {



  while(lista != NULL) {

    exec_instr(INSTR(lista));
    lista = NXT(lista);

  }



  printf("________\n");
  print(Hashtable);
  printf("________\n");

}

void exec_instr(Instr *command) {

  switch (KIND(command)) {
    // case ATRIB:
    //   if (DEBUG) printf("ATRIB\n");
    //   if (DEBUG) printf("_%s_\n", NAMECMD(command));
    //   lookup(Hashtable, NAMECMD(command), VALCMD(command),1);
    //   break;
    case ADD:
      if (DEBUG) printf("ADD\n");
      break;
    case SUB:
      if (DEBUG) printf("SUB\n");
      break;
    case MUL:
      if (DEBUG) printf("MUL\n");
      break;
    case DIV:
      if (DEBUG) printf("DIV\n");
      break;
    case IF_I:
      if (DEBUG) printf("IF_I\n");
      break;
    case PRINT:
      if (DEBUG) printf("PRINT\n");
      break;
    case READ:
      if (DEBUG) printf("READ\n");
      break;
    case GOTO_I:
      if (DEBUG) printf("GOTO_I\n");
      break;
    case LABEL_I:
      if (DEBUG) printf("LABEL_I\n");
      break;
    case QUIT_I:
      if (DEBUG) printf("QUIT_I\n");
      return;
  }


}

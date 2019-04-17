#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instr.h"

char *keywords[SIZEKEYW] =  {".ler(", ".if", ".escrever(", ".goto", ".label", ".quit", "+", "-", "*", "/"};

Instr *new_instr(OpKind k, Elem *e1, Elem *e2, Elem *e3){
  Instr *i = (Instr*) malloc(sizeof(Instr));
  i->op = k;
  i->elem1 = e1;
  i->elem2 = e2;
  i->elem3 = e3;
  return i;
}

Elem *new_elem(ElemKind k, char *n, int v, float f){
  Elem *e = (Elem*) malloc(sizeof(Elem));
    e->kind = k;
  switch(k){
    case EMPTY:
      break;
    case INT_VAR:
    case FLOAT_VAR:
    case LABEL:
      e->contents.name = n;
      break;
    case INT_CONST:
      e->contents.intval = v;
      break;
    case FLOAT_CONST:
      e->contents.fvalue = f;
      break;
  }
  return e;
}

Instr* instrfy(char *linha) {
  Instr *in = NULL;
  char *token, *token2, *token3;
  char str[30];
  int i;
  //ciclo pra encontrar a needle
  for(i=0; i<SIZEKEYW; i++){
    token = strstr(linha, keywords[i]);
    if(token != NULL) break;
  }

  strcpy(str, linha);

  printf("pre switch\n");

  switch(i) {
    case 0: //ler(_);
      return(new_instr_RWL(str, READ, INT_VAR, "(", ")"));
    case 1: //if _ goto _
      return(new_instr_if(str));
    case 2: //escrever(_);
      return(new_instr_RWL(str, PRINT, INT_VAR, "(", ")"));
    case 3: //goto _
      return(new_instr_RWL(str, GOTO, LABEL, " ", "\0"));
    case 4: //label
      return(new_instr_RWL(str, LABEL_I, LABEL, " ", "\0"));
    case 5: //"-quit"
      return(new_instr(QUIT,NULL,NULL,NULL));
    case 6: // ADD
      return(new_instrfy_op(str, "+", ADD));
    case 7: // SUB
      return(new_instrfy_op(str, "-", SUB));
    case 8: // MUL
      return(new_instrfy_op(str, "*", MUL));
    case 9: // DIV
      return(new_instrfy_op(str, "/", DIV));
    case 10: // ATRIB
      return(new_instr_atrib(str));
    default:
      printf("ERRO\n");
    }
    return NULL;
}

Instr* new_instr_RWL(char str[], OpKind opk, ElemKind elk, char delim1[], char delim2[]){
  char *token;
  strtok(str, "(");
  token = strtok(NULL, ")");
  return (new_instr(opk, new_elem(elk, token, 0, 0), NULL, NULL));
}

Instr* new_instr_if(char str[]){
  char* token, token2;
  strtok(str, " ");
  token = strtok(NULL, " goto "); // token = (condition)
  strtok(NULL," ");
  token2 = strtok(NULL, "\0"); // token = LX
  return (new_instr(IF, new_elem(INT_VAR, token, 0, 0), new_elem(LABEL, token, 0, 0), NULL));
}

Instr* new_instr_op(char str[], char op[], OpKind k){
  char *token, token2, token3;
  int v;
  token = strtok(str, ".");
  token = strtok(token, "=");
  token2 = strtok(NULL, op);
  token3 = strtok(NULL, "\0");
  return(new_instr(k, new_elem(INT_VAR, token, 0, 0), is_number(token2), is_number(token3)));
}

Instr* new_instr_atrib(char str[]){
  char *token, *token2;
  token = strtok(str, ".");
  token = strtok(token, "=");
  token2 = strtok(NULL, "\0");
  return(new_instr(ATRIB, token, token2, NULL));
}

Elem *is_number(char *token){
  int v;
  if((v=atoi(token)) != 0 || strcmp(token, "0") == 0){
    return(new_elem(INT_CONST, NULL, v, 0));
    }
  else{
    return(new_elem(INT_VAR, token, 0, 0));
  }
}

void print_instr(Instr* i){
  printf("Instruction: %d", i->op);
  print_elem(i->elem1);
  print_elem(i->elem2);
  print_elem(i->elem3);
}

void print_elem(Elem* e){
  switch(e->kind){
    case EMPTY:
        printf("EMPTY\n");
      break;
    case INT_VAR:
    case FLOAT_VAR:
    case LABEL:
      printf("name: %s\n", e->contents.name);
      break;
    case INT_CONST:
      printf("int: %d\n", e->contents.intval);
      break;
    case FLOAT_CONST:
      printf("float: %f\n", e->contents.fvalue);
      break;
  }
}
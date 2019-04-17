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
      if (DEBUG) printf("case 0\n");
      strtok(str, "(");
      token = strtok(NULL, ")");
      if (DEBUG) printf("|%s|\n", token);
      return(new_instr(READ, new_elem(INT_VAR, token, 0, 0), NULL, NULL);
      break;
    case 1: //if _ goto _
      if (DEBUG) printf("case 1\n");
      strtok(str, " ");
      token = strtok(NULL, " goto "); // token = (condition)
      if (DEBUG) printf("|%s|\n", token);
      strtok(NULL," ");
      token2 = strtok(NULL,"\0"); // token = LX
      if (DEBUG) printf("|%s|\n", token2);
      return (new_instr(IF, new_elem(INT_VAR, token, 0, 0), new_elem(INT_CONST, token, 0, 0), NULL));
      break;
    case 2: //escrever(_);
      if (DEBUG) printf("case 2\n");
      strtok(str, "(");
      token = strtok(NULL, ")");
      if (DEBUG) printf("|%s|\n",token);
      return (new_instr(PRINT, new_elem(INT_VAR, token, 0, 0), NULL, NULL));
      break;
    case 3: //goto _
      if (DEBUG) printf("case 3\n");
      strtok(str, " ");
      token = strtok(token, "\0");
      if (DEBUG) printf("|%s|\n",token);
      return(new_instr(GOTO, new_elem(LABEL, token, 0, 0), NULL, NULL));
      break;
    case 4: //label
      if (DEBUG) printf("case 4\n");
      strtok(str, " ");
      token = strtok(token, "\0");
      if (DEBUG) printf("|%s|\n",token);
      return(new_instr(LABEL_I, new_elem(LABEL, token, 0, 0), NULL, NULL));
      break;
    case 5: //"-quit"
      if (DEBUG) printf("case 5\n");
      return(new_instr(QUIT,NULL,NULL,NULL));
      break;
    case 6: // ADD
      return(aux_instrfy_op(str, "+", ADD));
    case 7: // SUB
      return(aux_instrfy_op(str, "-", SUB));
    case 8: // MUL
     return(aux_instrfy_op(str, "*", MUL));
    case 9: // DIV
      return(aux_instrfy_op(str, "/", DIV));
    case 10: // ATRIB
      if (DEBUG)  printf("case 10\n");
      token = strtok(str, ".");
      token = strtok(token, "=");
      if (DEBUG) printf("%s\n",token);
      token2 = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token2);
      in = new_instr(ATRIB, token, token2, NULL);
      break;
    default:
      printf("ERRO\n");

    }
    return in;
}


Instr* aux_instrfy_op(char str[], char op[], OpKind k){
  char *token, token2, token3;
  Elem *e1, *e2, *e3;
  int v;
  token = strtok(str, ".");
  e1 = new_elem(INT_VAR, token, 0, 0);
  token = strtok(token, "=");
  token2 = strtok(NULL, op);
  e2 = is_number(token2);
  token3 = strtok(NULL, "\0");
  e3 = is_number(token3); 
  return(new_instr(k,e1, e2, e3));
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
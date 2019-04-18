#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instr.h"

char *keywords[SIZEKEYW] =  {".ler(", ".if", ".escrever(", ".goto", ".label", ".quit", "+", "-", "*", "/"};

Instr new_instr(OpKind k, Elem e1, Elem e2, Elem e3){
  Instr i;
  i.op = k;
  i.elem1 = e1;
  printf("new_instr - n: %s\n", i.elem1.contents.name);
  i.elem2 = e2;
  i.elem3 = e3;
  return i;
}

Elem new_elem_empty() {
  Elem e;
  e.kind = EMPTY;
  return e;
}

Elem new_elem(ElemKind k, char *n, int v, float f) {
  Elem e;
    e.kind = k;
  switch(k){
    case EMPTY:
      break;
    case INT_VAR:
    case FLOAT_VAR:
    case LABEL:

      e.contents.name = strdup(n);
      printf("n: %s\n", e.contents.name);
      return e;
      break;
    case INT_CONST:
      e.contents.intval = v;
      return e;
      break;
    case FLOAT_CONST:
      e.contents.fvalue = f;
      return e;
      break;
  }
  return e;
}

Instr instrfy(char *linha) {
  char *token;
  char str[30];
  int i;
  //ciclo pra encontrar a needle
  for(i=0; i<SIZEKEYW; i++){
    token = strstr(linha, keywords[i]);
    if(token != NULL) break;
  }

  strcpy(str, linha);

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
      return(new_instr(QUIT,new_elem(EMPTY,NULL,0,0),new_elem(EMPTY,NULL,0,0),new_elem(EMPTY,NULL,0,0)));
    case 6: // ADD
      return(new_instr_op(str, "+", ADD));
    case 7: // SUB
      return(new_instr_op(str, "-", SUB));
    case 8: // MUL
      return(new_instr_op(str, "*", MUL));
    case 9: // DIV
      return(new_instr_op(str, "/", DIV));
    case 10: // ATRIB
      return(new_instr_atrib(str));
    default:
      printf("ERRO\n");
    }
    return new_instr(ERROR,new_elem(EMPTY,NULL,0,0),new_elem(EMPTY,NULL,0,0),new_elem(EMPTY,NULL,0,0));
}

Instr new_instr_RWL(char str[], OpKind opk, ElemKind elk, char delim1[], char delim2[]){
  char *token;
  strtok(str, delim1);
  token = strtok(NULL, delim2);
  printf("token: %s\n",token);
  return (new_instr(opk, new_elem(elk, token, 0, 0), new_elem(EMPTY,NULL,0,0), new_elem(EMPTY,NULL,0,0)));
}

Instr new_instr_if(char str[]){
  char* token, *token2;
  strtok(str, " ");
  token = strtok(NULL, " goto "); // token = (condition)
  strtok(NULL," ");
  token2 = strtok(NULL, "\0"); // token = LX
  return (new_instr(IF, new_elem(INT_VAR, token, 0, 0), new_elem(LABEL, token2, 0, 0), new_elem(EMPTY,NULL,0,0)));
}

Instr new_instr_op(char str[], char op[], OpKind k){
  char *token, *token2, *token3;
  token = strtok(str, ".");
  token = strtok(token, "=");
  token2 = strtok(NULL, op);
  token3 = strtok(NULL, "\0");
  return(new_instr(k, new_elem(INT_VAR, token, 0, 0), is_number(token2), is_number(token3)));
}

Instr new_instr_atrib(char str[]){
  char *token, *token2;
  token = strtok(str, ".");
  token = strtok(token, "=");
  token2 = strtok(NULL, "\0");
  return(new_instr(ATRIB, new_elem(INT_VAR, token, 0, 0), is_number(token2),new_elem(EMPTY,NULL,0,0)));
}

Elem is_number(char *token){
  int v;
  float f;

  if ((strstr(token,".")!=NULL || strstr(token,",")!=NULL) && (f = atof(token)) != 0.0) {
      return(new_elem(FLOAT_CONST, NULL, 0,f));
  }

  else if((v=atoi(token)) != 0 || strcmp(token, "0") == 0) {
    return(new_elem(INT_CONST, NULL, v, 0));
  }

  else {
    return(new_elem(INT_VAR, token, 0, 0));
  }

}

void print_instr(Instr i){
  printf("Instruction: %d\n", i.op);
  // printf("EL1\n");
  // printf("pos print_instr name: !%s!\n", i.elem1.contents.name);
  print_elem(i.elem1);
  // printf("EL2\n");
  print_elem(i.elem2);
  // printf("EL3\n");
  print_elem(i.elem3);
}

void print_elem(Elem e){
  switch(e.kind){
    case EMPTY:
        printf("EMPTY\n");
      break;
    case INT_VAR:
    case FLOAT_VAR:
    case LABEL:
      printf("name: %s\n", e.contents.name);
      break;
    case INT_CONST:
      printf("int: %d\n", e.contents.intval);
      break;
    case FLOAT_CONST:
      printf("float: %f\n", e.contents.fvalue);
      break;
  }
}

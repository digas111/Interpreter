#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instr.h"

Instr *new_instr(OpKind k,char *e1, char *e2, char *e3){
    Instr *i = (Instr*) malloc(sizeof(Instr));
    i->op = k;
    i->elem1 = e1;
    i->elem2 = e2;
    i->elem3 = e3;
    return i;
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


  //////////////////

  strcpy(str, linha);

  //////////////////

  printf("pre switch\n");

  switch(i) {
    case 0: //ler(_);
      if (DEBUG) printf("case 0\n");
      strtok(str, "(");
      token = strtok(NULL, ")");
      if (DEBUG) printf("|%s|\n", token);
      in = new_instr(READ, token, NULL, NULL);
      break;
    case 1: //if _ goto _
      if (DEBUG) printf("case 1\n");
      strtok(str, " ");
      token = strtok(NULL, " goto "); // token = (condition)
      if (DEBUG) printf("|%s|\n", token);
      strtok(NULL," ");
      token2 = strtok(NULL,"\0"); // token = LX
      if (DEBUG) printf("|%s|\n", token2);
      in = new_instr(IF, token, token2, NULL);
      break;
    case 2: //escrever(_);
      if (DEBUG) printf("case 2\n");
      strtok(str, "(");
      token = strtok(NULL, ")");
      if (DEBUG) printf("|%s|\n",token);
      in = new_instr(PRINT, token, NULL, NULL);
      break;
    case 3: //goto _
      if (DEBUG) printf("case 3\n");
      strtok(str, " ");
      token = strtok(token, "\0");
      if (DEBUG) printf("|%s|\n",token);
      in = new_instr(GOTO, token, NULL, NULL);
      break;
    case 4: //label
      if (DEBUG) printf("case 4\n");
      strtok(str, " ");
      token = strtok(token, "\0");
      if (DEBUG) printf("|%s|\n",token);
      in = new_instr(LABEL, token, NULL, NULL);
      break;
    case 5: //"-quit"
      if (DEBUG) printf("case 5\n");
      in = new_instr(QUIT,NULL,NULL,NULL);
      break;
    case 6: // ADD
      if (DEBUG) printf("case 6\n");
      token = strtok(str, ".");
      if (DEBUG) printf("%s\n",token);
      token = strtok(token, "=");
      if (DEBUG) printf("%s\n",token);
      token2 = strtok(NULL, "+");
      if (DEBUG) printf("%s\n",token2);
      token3 = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token3);
      in = new_instr(ADD, token, token2, token3);
      break;
    case 7: // SUB
      if (DEBUG) printf("case 7\n");
      token = strtok(str, ".");
      if (DEBUG) printf("%s\n",token);
      token = strtok(token, "=");
      if (DEBUG) printf("%s\n",token);
      token2 = strtok(NULL, "-");
      if (DEBUG) printf("%s\n",token2);
      token3 = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token3);
      in = new_instr(SUB, token, token2, token3);
      break;
    case 8: // MUL
      if (DEBUG) printf("case 8\n");
      token = strtok(str, ".");
      if (DEBUG) printf("%s\n",token);
      token = strtok(token, "=");
      if (DEBUG) printf("%s\n",token);
      token2 = strtok(NULL, "*");
      if (DEBUG) printf("%s\n",token2);
      token3 = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token3);
      in = new_instr(MUL, token, token2, token3);
      break;
    case 9: // DIV
      if (DEBUG) printf("case 9\n");
      token = strtok(str, ".");
      if (DEBUG) printf("%s\n",token);
      token = strtok(token, "=");
      if (DEBUG) printf("%s\n",token);
      token2 = strtok(NULL, "-");
      if (DEBUG) printf("%s\n",token2);
      token3 = strtok(NULL, "\0");
      if (DEBUG) printf("%s\n",token3);
      in = new_instr(SUB, token, token2, token3);
      break;
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


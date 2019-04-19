#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "read.h"



char* string_add_last(char string[], int *size, char c) {

  int n = *size;

  string = (char *) realloc(string,(n+1)*sizeof(char));

  string[n] = c;

  n++;

  *size = n;

  return string;

}

char* dell_spaces(char *input) {

  int i,j=0;

  char *output;

  output = (char *) malloc(j);

  for (i=0; input[i]!='\0'; i++) {

    if (input[i]!=' ') {
      output = (char *) realloc(output,j+1);
      output[j] = input[i];
      j++;
    }

  }

  return output;

}

NODE *file_to_llist(char file_name[], NODE *lista_instr, HASHNODE *hashtable[]) {

  FILE * code;
  code = fopen(file_name, "r");

  char c;

  int i=0;

  if (code) {
    while ((c = getc(code)) != EOF) {

      int flag = 0;

      if (c != '\n') {
        i++;

        char *line;
        int index = 0;
        line = (char *) malloc(index*sizeof(char));

        line = string_add_last(line,&index,'.');
        line = string_add_last(line,&index,c);

        while ((c = getc(code)) != ';') {

          if (c == '=') {
            flag = 1;
          }

          line = string_add_last(line,&index,c);

        }

        line = string_add_last(line,&index,'\0');

        if (flag) {
          line = dell_spaces(line);
        }

        printf("line %d: %s-\n", i,line);

        lista_instr = process_line(line, lista_instr, hashtable);

        //Instr new = instrfy(line);

        //void process_instr(new);



      }

    }
  }

  fclose(code);
  return lista_instr;

}

NODE *process_line(char *line,NODE *lista_instr, HASHNODE *hashtable[]) {

  Instr new_instr = instrfy(line);

  lista_instr = add_last(lista_instr,instrfy(line));

  if (INSTROP(new_instr) == LABEL_I) {

    union hash data;
    data.label = last(lista_instr);

    save(hashtable,INSTREELEM1(new_instr),data);

  }


  return lista_instr;

}


void exec_list(NODE *lista_instr, HASHNODE *hashtable[]) {
  while(lista_instr != NULL){
    switch(INSTROP(INSTR(lista_instr))){
      case 0: //READ
        exec_read(INSTR(lista_instr), hashtable);
        break;
      case 1: //PRINT
        exec_print(INSTR(lista_instr), hashtable);
        break;
      case 2: //IF
        //exec_if(INSTR(lista_instr), hashtable);
        break;
      case 3: //GOTO
        //exec_goto(INSTR(lista_instr), hashtable);
        break;
      case 4: //LABEL_I
        //exec_label(INSTR(lista_instr), hashtable);
        break;
      case 5: //QUIT
        return;
      case 6: //ADD
        //exec_conta(INSTR(lista_instr), hashtable);
        break;
      case 7: //SUB
        //exec_conta(INSTR(lista_instr), hashtable);
        break;
      case 8: //DIV
        //exec_conta(INSTR(lista_instr), hashtable);
        break;
      case 9: //MUL
        //exec_conta(INSTR(lista_instr), hashtable);
        break;
      case 10: //ATRIB
        //exec_conta(INSTR(lista_instr), hashtable);
        break;
      default:
      break;
    }
  }
}

char* get_var() {
  int i=0;
  char c;
  char *token = NULL;

  for (i=0; (c = getc(stdin)) != '\n'; i++) {
    token[i] = c;
  }

  token = string_add_last(token,&i,'\0');

  return token;

}


void exec_read(Instr i, HASHNODE *hashtable[]) {
  char *token = get_var();

  save(hashtable,INSTREELEM1(i),var(token));

}

void exec_print(Instr i, HASHNODE *hashtable[]){
}
//
// NODE *exec_if(){
//
// }

union hash var(char *token) {

  union hash data;
  float f;

  if ((strstr(token,".")!=NULL || strstr(token,",")!=NULL) && (f = atof(token)) != 0.0) {
    data.fvalue = f;
    return data;
  }

  else {
    data.ivalue = atoi(token);
  }

  return data;

}

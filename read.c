#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "read.h"

NODE *lista_instr = NULL;

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

void file_to_llist(char file_name[]) {

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

        // Instr *instr = instrfy(line);
        //
        // printf("aqui\n");
        // printf("OpKind = %d\n", instr->op);
        // printf("First.name: _%s_\n",instr->first->contents.inte.name);
        // printf("Second.name: _%s_\n",instr->second->contents.inte.name);
        // printf("Third.name: _%s_\n\n",instr->third->contents.inte.name);


        lista_instr = add_last(instrfy(line),lista_instr);


        printf("line %d: %s-\n", i,line);


      }

    }
  }

  fclose(code);

}

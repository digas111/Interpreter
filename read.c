#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "read.h"

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

void file_to_llist() {

  FILE * code;
  code = fopen("test.txt", "r");

  char c;

  int i=0;

  if (code) {
    while ((c = getc(code)) != EOF) {

      int flag = 0;

      if (c != '\n') {
        i++;

        char *line;
        int index = 0;

        line = (char *) malloc(index+1);

        line[0] = c;

        while ((c = getc(code)) != ';') {

          if (c == '=') {
            flag = 1;
          }

          index++;

          line = (char *) realloc(line,index+1);

          line[index] = c;

        }

        if (flag) {
          line = dell_spaces(line);
        }

        printf("line %d: -%s-\n", i,line);

      }

    }
  }

  fclose(code);

}

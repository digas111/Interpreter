#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"

char *string_add_last(char string[], int *size, char c) {
  int n = *size;

  string = (char *)realloc(string, (n + 1) * sizeof(char));

  string[n] = c;

  n++;

  *size = n;

  return string;
}

char *dell_spaces(char *input) {
  int i, j = 0;

  char *output;

  output = (char *)malloc(j);

  for (i = 0; input[i] != '\0'; i++) {
    if (input[i] != ' ') {
      output = (char *)realloc(output, j + 1);
      output[j] = input[i];
      j++;
    }
  }

  return output;
}

NODE *file_to_llist(char file_name[], NODE *lista_instr, HASHNODE *hashtable[]) {
  FILE *code;
  if ((code = fopen(file_name, "r")) == NULL) {
    perror("Error: ");
    exit(-1);
  }

  char c;

  int i = 0;

  if (code) {
    while ((c = getc(code)) != EOF) {
      int flag = 0;

      if (c != '\n') {
        i++;

        char *line;
        int index = 0;
        line = (char *)malloc(index * sizeof(char));

        line = string_add_last(line, &index, c);

        while ((c = getc(code)) != ';') {
          if (c == '=') {
            flag = 1;
          }

          if (c == ',') {
            c = '.';
          }

          line = string_add_last(line, &index, c);
        }

        line = string_add_last(line, &index, '\0');

        if (flag) {
          line = dell_spaces(line);
        }

        lista_instr = process_line(line, lista_instr, hashtable);
      }
    }
  }

  fclose(code);
  return lista_instr;
}

NODE *process_line(char *line, NODE *lista_instr, HASHNODE *hashtable[]) {
  Instr new_instr = instrfy(line);
  lista_instr = add_last(lista_instr, new_instr);

  if (INSTROP(new_instr) == LABEL_I) {
    union hash data;
    data.label = last(lista_instr);

    save(hashtable, INSTREELEM1(new_instr), data);
  }

  return lista_instr;
}

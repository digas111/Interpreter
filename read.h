#ifndef READ_H
#define READ_H

#include "hash.h"
#include "linkedlist.h"

#define VARSIZE 25

//----------------------------------------

char *dell_spaces(char *input);
NODE *file_to_llist(char file_name[], NODE *lista_instr, HASHNODE *hashtable[]);
char *string_add_last(char string[], int *size, char c);
NODE *process_line(char *line, NODE *lista_instr, HASHNODE *hashtable[]);

//----------------------------------------

#endif

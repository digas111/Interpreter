#ifndef READ_H
#define READ_H

#include "linkedlist.h"
#include "hash.h"

#define VARSIZE 25

//----------------------------------------

char* dell_spaces(char *input);
NODE *file_to_llist(char file_name[], NODE *lista_instr, HASHNODE *hashtable[]);
char* string_add_last(char string[], int *size, char c);
NODE *process_line(char *line,NODE *lista_instr, HASHNODE *hashtable[]);
void exec_list(NODE *lista_instr, HASHNODE *hashtable[]);
void exec_read(Instr i, HASHNODE *hastable[]);
void exec_print(Instr i, HASHNODE *hashtable[]);
NODE *exec_if(Instr i, HASHNODE *hashnode[]);
NODE *exec_goto(Instr i, HASHNODE *hashtable[]);
void exec_add(Instr i, HASHNODE *hashtable[]);
void exec_sub(Instr i, HASHNODE *hashtable[]);
void exec_mul(Instr i, HASHNODE *hashtable[]);
void exec_div(Instr i, HASHNODE *hashtable[]);
void exec_atrib(Instr i, HASHNODE *hashtable[]);
union hash var(char *token) ;

//----------------------------------------



#endif

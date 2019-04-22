#ifndef EXEC_H
#define EXEC_H

#include "hash.h"
#include "linkedlist.h"

//----------------------------------------

void exec_list(NODE *lista_instr, HASHNODE *hashtable[]);
void exec_read(Instr i, HASHNODE *hastable[]);
void exec_print(Instr i, HASHNODE *hashtable[]);
NODE *exec_if(Instr i, HASHNODE *hashnode[]);
NODE *exec_goto(Instr i, HASHNODE *hashtable[]);
float is_int(float a);
float get_val(Elem e, HASHNODE *hashtable[]);
void save_result(Elem e, HASHNODE *hashtable[], float r);
void exec_add(Instr i, HASHNODE *hashtable[]);
void exec_sub(Instr i, HASHNODE *hashtable[]);
void exec_mul(Instr i, HASHNODE *hashtable[]);
void exec_div(Instr i, HASHNODE *hashtable[]);
void exec_atrib(Instr i, HASHNODE *hashtable[]);

//----------------------------------------

#endif
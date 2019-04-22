#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "instr.h"

#define INSTR(P) ((P)->instr)
#define NXT(P) ((P)->nxt)

typedef struct node {
  Instr instr;
  struct node *nxt;
} NODE;

NODE *new_node(Instr instr);                 //cria um nó com uma instrucao
NODE *add_last(NODE *lista_instr, Instr i);  //adiciona ao fim da lista um no com uma instrucao
void print_llist();                          //imprime o conteudo da lista
NODE *last(NODE *lista_instr);               //retorna o ultimo elemento da lista

#endif

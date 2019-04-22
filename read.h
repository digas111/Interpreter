#ifndef READ_H
#define READ_H

#include "hash.h"
#include "linkedlist.h"

#define VARSIZE 25  //tamanho máximo para o nome de uma variável

//----------------------------------------

//coverte o ficheiro cujo nome é recebido (file_name) numa linkedlist de intruções nele contidas
NODE *file_to_llist(char file_name[], NODE *lista_instr, HASHNODE *hashtable[]);

/*        Auxiliares do file_to_llist       */
//processa a linha de codigo recebida chamando funções para criar e adicionar à lista uma instrução representativa dessa mesma linha
NODE *process_line(char *line, NODE *lista_instr, HASHNODE *hashtable[]);
//apaga os espaços contidos na char* recebida
char *dell_spaces(char *input);
//adiciona o char c no fim da string recebida
char *string_add_last(char string[], int *size, char c);
/*                                 */

//----------------------------------------

#endif

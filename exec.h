#ifndef EXEC_H
#define EXEC_H

#include "hash.h"
#include "linkedlist.h"

//----------------------------------------

//chama as funções que executam as intruções guardadas na linkedlist
void exec_list(NODE *lista_instr, HASHNODE *hashtable[]);

/*        Auxiliares do exec_list       */
//lê a variável pertendida do standard input
void exec_read(Instr i, HASHNODE *hastable[]);
//imprime a variável perdentida no standard output
void exec_print(Instr i, HASHNODE *hashtable[]);
//executa a instrução if returnando null caso a expressão seja falsa e o apontador para a LABEL pertendida caso seja verdadeira
NODE *exec_if(Instr i, HASHNODE *hashnode[]);
//avança ou retrocede a a execução do codigo para a LABEL pertendida
NODE *exec_goto(Instr i, HASHNODE *hashtable[]);
//Veririca se o valor recebido é um inteiro (não tem casas décimais) ou é um float (retorna 0 em caso afirmativo)
float is_int(float a);
//retorna o valor do elemento recebido
float get_val(Elem e, HASHNODE *hashtable[]);
//guarada o valor recebido como 'r' na hashtable fazendo-o corresponder ao nome do elemnto 'e'
void save_result(Elem e, HASHNODE *hashtable[], float r);
//soma as variàveis pertendidas
void exec_add(Instr i, HASHNODE *hashtable[]);
//subtrai as variàveis pertendidas
void exec_sub(Instr i, HASHNODE *hashtable[]);
//multiplica as variàveis pertendidas
void exec_mul(Instr i, HASHNODE *hashtable[]);
//divide as variàveis pertendidas
void exec_div(Instr i, HASHNODE *hashtable[]);
//guarda na hash a variável correspondente à instrução recebida
void exec_atrib(Instr i, HASHNODE *hashtable[]);
/*                                 */

//----------------------------------------

#endif
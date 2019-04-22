#include <stdio.h>
#include "exec.h"
#include "hash.h"
#include "instr.h"
#include "linkedlist.h"
#include "read.h"

int main(int argc, char **argv) {
  //cria a lista de instruções
  NODE *lista_instr = NULL;
  //cria a hashtable onde serão guardadas as variáveis e as LABELS
  HASHNODE *hashtable[NHASH];

  //inicializa a NULL a hashtable
  for (int i = 0; i < NHASH; i++) {
    hashtable[i] = NULL;
  }

  //guarda o nome do ficheiro recebido na variável
  char *file = argv[1];

  //guarda na lista de intruções todas as intruções contidas no ficheiro
  lista_instr = file_to_llist(file, lista_instr, hashtable);

  //executa as intruções continas na lista de intruções
  exec_list(lista_instr, hashtable);

  return 0;
}

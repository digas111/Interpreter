#include <stdio.h>
#include "hash.h"
#include "instr.h"
#include "linkedlist.h"
#include "read.h"
#include "exec.h"

#define MDEBUG 1

int main(int argc, char **argv) {
  NODE *lista_instr = NULL;
  HASHNODE *hashtable[NHASH];



  for (int i = 0; i < NHASH; i++) {
    hashtable[i] = NULL;
  }

  char *file = argv[1];

  lista_instr = file_to_llist(file, lista_instr, hashtable);

  exec_list(lista_instr, hashtable);

  return 0;
}

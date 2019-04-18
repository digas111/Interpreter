#include <stdio.h>
#include "read.h"
#include "hash.h"
#include "linkedlist.h"
#include "instr.h"

#define MDEBUG 1

int main(int argc, char **argv) {

  NODE *lista_instr = NULL;
  HASHNODE *hashtable[NHASH];

  char *file = argv[1];

  lista_instr = file_to_llist(file, lista_instr, hashtable);

  if (MDEBUG) {

    // union hash data;
    // data.ivalue = 2;
    //
    // save(hashtable,INT,"var",data);
    // data.fvalue = 2.2;
    // save(hashtable,FLOAT,"var2",data);

    print_llist(lista_instr);

    printf("__________EXEC_______\n");

    exec_list(lista_instr, hashtable);

    printf("_____________________\n");

    print_hash(hashtable);


  }

  return 0;

}

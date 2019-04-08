#include <stdio.h>
#include "estrutura.h"
#include "hash.h"
#include "read.h"
#define DEBUGMODE 1

HASHNODE *Hashtable[NHASH];

int main(int argc, char** argv) {

  char *file = argv[1];

  printf("--%s\n", file);

  if (DEBUGMODE) {

    file_to_llist(file);

    printf("\n\n");

    lookup(Hashtable,"boas",2,1);
    lookup(Hashtable,"comandos",3,1);
    lookup(Hashtable,"cenas",1,1);
    lookup(Hashtable,"coisas",4,1);
    lookup(Hashtable,"sjjs",5,1);

    print(Hashtable);

    NODE *lista = NULL;

    Elem *e1= new_elem_int(INT_CONST, 1, "name");
    Elem *e2= new_elem_int(INT_CONST, 1, "name");
    Elem *e3= new_elem_int(INT_CONST, 1, "name");

    Instr *instru = new_instr(ADD, e1, e2, e3);

    lista=new_node(instru, lista);
    lista=new_node(instru, lista);
    lista=new_node(instru, lista);
    lista=new_node(instru, lista);
    lista=new_node(instru, lista);
    lista=new_node(instru, lista);
    lista=new_node(instru, lista);

    int n = length(lista);
    printf("%d\n", n);

    return 0;
  }
}

#include <stdio.h>
#include "read.h"
#define DEBUGMODE 1



int main(int argc, char** argv) {

  NODE *lista_instr = NULL;

  char *file = argv[1];

  printf("--%s\n", file);

  if (DEBUGMODE) {

    lista_instr = file_to_llist(file, lista_instr);
    run_program(lista_instr);
    //print_lista(lista_instr);

    //printf("\n\n");

    // lookup(Hashtable,"boas",2,1);
    // lookup(Hashtable,"comandos",3,1);
    // lookup(Hashtable,"cenas",1,1);
    // lookup(Hashtable,"coisas",4,1);
    // lookup(Hashtable,"sjjs",5,1);
    //
    // print(Hashtable);

    // NODE *lista = NULL;

    // Elem *e1= new_elem_int(INT_CONST, 1, "name");
    // Elem *e2= new_elem_int(INT_CONST, 1, "name");
    // Elem *e3= new_elem_int(INT_CONST, 1, "name");
    //
    // Instr *instru = new_instr(ADD, e1, e2, e3);

    // lista=new_node(instru, lista);
    // lista=new_node(instru, lista);
    // lista=new_node(instru, lista);
    // lista=new_node(instru, lista);
    // lista=new_node(instru, lista);
    // lista=new_node(instru, lista);
    // lista=new_node(instru, lista);

    // int n = length(lista);
    // printf("%d\n", n);

    return 0;
  }
}

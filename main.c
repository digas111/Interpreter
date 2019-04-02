#include <stdio.h>
#include "estrutura.h"
#include "hash.h"
#define DEBUGMODE 1

int main(){

  if (DEBUGMODE){

    lookup("boas", 2, 1);
    lookup("comandos", 3, 1);
    lookup("cenas", 1, 1);
    lookup("coisas", 4, 1);
    lookup("sjjs", 5, 1);

    print();
    NODE *lista = NULL;

    Elem *e1 = new_elem_int(INT_CONST, 1, "name");
    Elem *e2 = new_elem_int(INT_CONST, 1, "name");
    Elem *e3 = new_elem_int(INT_CONST, 1, "name");

    Instr *instru = new_instr(ADD, e1, e2, e3);

    lista = new_node(instru, lista);
    lista = new_node(instru, lista);
    lista = new_node(instru, lista);
    lista = new_node(instru, lista);
    lista = new_node(instru, lista);
    lista = new_node(instru, lista);
    lista = new_node(instru, lista);

    int n = length(lista);
    printf("%d\n", n);

    return 0;
  }
}

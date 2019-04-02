#include <stdio.h>
#include "estrutura.h"

#define DEBUGMODE 1

int main(){

  if(DEBUGMODE){
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
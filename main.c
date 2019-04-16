#include <stdio.h>
#include "hash.h"
#include "linkedlist.h"
#include "instr.h"

#define MDEBUG 1


int main(int argc, char **argv) {

  //char *file = argv[1];

  if (MDEBUG) {

    union hash data;
    data.ivalue = 2;

    save(INT,"var",data);
    data.fvalue = 2.2;
    save(FLOAT,"var2",data);
    print();

  }



  return 0;

}

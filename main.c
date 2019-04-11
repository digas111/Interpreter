#include <stdio.h>
#include "hash.h"
#include "variablehash.h"
#include "labelhash.h"
#include "linkedlist.h"
#include "instr.h"


#define DEBUG 1

int main(int argc, char **argv) {


 VHASHNODE *variables[NHASH];

 vsave(variables, "boas", 1);
 //
 // print(variables);

 return 0;

}

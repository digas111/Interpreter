#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "variablehash.h"
#include "hash.h"

//VHASHNODE *Hashtable[NHASH];

VHASHNODE *new_vhashnode(char *name, int value, VHASHNODE *next) {
  VHASHNODE *l = (VHASHNODE *) malloc (sizeof (VHASHNODE));
  NAME(l) = name;
  VVALUE(l) = value;
  NEXT(l) = next;
  return l;
}

VHASHNODE *get_var(VHASHNODE *in_hash[], char *name) {

  unsigned int i = hash(name);
  VHASHNODE *l = in_hash[i];

  while(l != NULL) {
    if (strcmp(name, NAME(l))==0) {
      return l;
    }
    l = NEXT(l);
  }

  return NULL;

}

//saves the variabel's value
VHASHNODE *vsave(VHASHNODE *in_hash[], char *name, int value) {

  unsigned int i = hash(name);
  VHASHNODE *l = in_hash[i];

  while(l!=NULL) {

    if (strcmp(name, NAME(l))==0) {
      VVALUE(l) = value;
      return l;
    }

    l = NEXT(l);

  }

  l = new_vhashnode(name, value,in_hash[i]);

  return l;


}



//print the hash
void print(VHASHNODE *in_hash[]) {

  int i=0;
  VHASHNODE *l;

  for(i=0; i<NHASH;i++) {
    if ((l = in_hash[i])!=NULL) {
      while(l!=NULL) {
        printf("NAME: %s - VALUE:%d\n", NAME(l),VVALUE(l));
        l = NEXT(l);
      }
      printf("\n");
    }
    else {
      printf("~~\n");
    }
  }

}

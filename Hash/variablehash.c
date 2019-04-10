#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "variablehash.h"

//VHASHNODE *Hashtable[NHASH];

VHASHNODE *new_vhashnode(char *name, int value, VHASHNODE *next) {
  VHASHNODE *l = (VHASHNODE *) malloc (sizeof (VHASHNODE));
  HNAME(l) = name;
  HVALUE(l) = value;
  HNEXT(l) = next;
  return l;
}

unsigned int hash(char *str) {
 unsigned int res = 0;

 while(*str != '\0'){

  res = res * MULTIPLICADOR + *str;
  str++;

 }
 return res%NHASH;
}

int get_value(VHASHNODE *in_hash[], char *name) {


  unsigned inti = hash(name);
  VHASHNODE *l = in_hash[i];

  while(l != NULL) {
    if (strcmp(name, HNAME(l))==0) {
      return HVALUE(l);
    }
    l = HNEXT(l);
  }

  return NULL;

}

//saves the variabel's value
VHASHNODE *save(VHASHNODE *in_hash[], char *name, int value) {

  unsigned int i = hash(name);
  VHASHNODE *l = in_hash[i];

  while(l!=NULL) {

    if (strcmp(name, HNAME(l))==0) {
      HVALUE(l) = value;
      return l;
    }

    l = HNEXT(l);

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
        printf("NAME: %s - VALUE:%d\n", HNAME(l),HVALUE(l));
        l = HNEXT(l);
      }
      printf("\n");
    }
    else {
      printf("~~\n");
    }
  }

}

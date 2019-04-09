#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "hash.h"

//HASHNODE *Hashtable[NHASH];

HASHNODE *new_hashnode(char *name, int value, HASHNODE *next) {
  HASHNODE *l = (HASHNODE *) malloc (sizeof (HASHNODE));
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

int get_value(HASHNODE *in_hash[], char *name) {


  unsigned inti = hash(name);
  HASHNODE *l = in_hash[i];

  while(l != NULL) {
    if (strcmp(name, HNAME(l))==0) {
      return HVALUE(l);
    }
    l = HNEXT(l);
  }

  return NULL;

}

//saves the variabel's value
HASHNODE *save(HASHNODE *in_hash[], char *name, int value) {

  unsigned int i = hash(name);
  HASHNODE *l = in_hash[i];

  while(l!=NULL) {

    if (strcmp(name, HNAME(l))==0) {
      HVALUE(l) = value;
      return l;
    }

    l = HNEXT(l);

  }

  l = new_hashnode(name, value,in_hash[i]);

  return l;


}



//print the hash
void print(HASHNODE *in_hash[]) {

  int i=0;
  HASHNODE *l;

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

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "hash.h"

#define NHASH 4
#define MULTIPLICADOR 31

NODE *Hashtable[NHASH];

NODE *new_node(char *name, int value, NODE *next) {
  NODE *l = (NODE *) malloc (sizeof (NODE));
  NAME(l) = name;
  VALUE(l) = value;
  NEXT(l) = next;
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

NODE *lookup(char *name, int value, int create) {

 //se existir name na tabela de hash
 // retornar o seu valor
 // se não exitir e create for 1
 //  criar o no com name e value

 unsigned int i = hash(name);
 NODE * l = Hashtable[i];

 while(l != NULL) {
  if (strcmp(name, NAME(l))==0) {
   return l;
  }
  l = NEXT(l);
 }

 if (create) {
  l = new_node(name, value,Hashtable[i]);
  Hashtable[i] = l;
 }

 return l;
}

void print() {

  int i=0;
  NODE *l;

  for(i=0; i<NHASH;i++) {
    if ((l = Hashtable[i])!=NULL) {
      while(l!=NULL) {
        printf("NAME: %s - VALUE:%d\n", NAME(l),VALUE(l));
        l = NEXT(l);
      }
      printf("\n");

    }
    else {
      printf("~~\n");
    }
  }

}

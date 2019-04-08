#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "hash.h"

//HASHNODE *Hashtable[NHASH];

HASHNODE *new_hashnode(char *name, int value, HASHNODE *next) {
  HASHNODE *l = (HASHNODE *) malloc (sizeof (HASHNODE));
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

HASHNODE *lookup(HASHNODE *in_hash[], char *name, int value, int create) {

printf("******************************************************\n");

 //se existir name na tabela e criar for 1 -> substitui o valor
 //se existir name na tabela e criar for 0 -> retorna o seu valor
 //se não existir e criar for 1 cria um novo elemento

 unsigned int i = hash(name);
 HASHNODE * l = in_hash[i];

 while(l != NULL) {
  if (strcmp(name, NAME(l))==0) {
    if (create) {
      VALUE(l) = value;
    }
   return l;
  }
  l = NEXT(l);
 }

 if (create) {

  l = new_hashnode(name, value,in_hash[i]);
  in_hash[i] = l;
 }

 return l;
}

void print(HASHNODE *in_hash[]) {

  int i=0;
  HASHNODE *l;

  for(i=0; i<NHASH;i++) {
    if ((l = in_hash[i])!=NULL) {
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

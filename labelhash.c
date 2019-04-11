#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "labelhash.h"
#include "hash.h"

//LHASHNODE *Hashtable[NHASH];

LHASHNODE *new_lhashnode(char *name, NODE *label, LHASHNODE *next) {
  LHASHNODE *l = (LHASHNODE *) malloc (sizeof (LHASHNODE));
  NAME(l) = name;
  LNODE(l) = label;
  NEXT(l) = next;
  return l;
}

//return the label NODE
NODE *get_label(LHASHNODE *in_hash[], char *name) {

  unsigned int i = hash(name);
  LHASHNODE *l = in_hash[i];

  while(l != NULL) {
    if (strcmp(name, NAME(l))==0) {
      return LNODE(l);
    }
    l = NEXT(l);
  }

  return NULL;

}

//saves the variabel's value
LHASHNODE *lsave(LHASHNODE *in_hash[], char *name, NODE *label) {

  unsigned int i = hash(name);
  LHASHNODE *l = in_hash[i];

  while(l!=NULL) {

    if (strcmp(name, NAME(l))==0) {
      LNODE(l) = label;
      return l;
    }

    l = NEXT(l);

  }

  l = new_lhashnode(name, label,in_hash[i]);

  return l;


}

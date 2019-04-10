#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "labelhash.h"

//LHASHNODE *Hashtable[NHASH];

LHASHNODE *new_lhashnode(char *name, NODE *label,int value, LHASHNODE *next) {
  LHASHNODE *l = (LHASHNODE *) malloc (sizeof (LHASHNODE));
  HNAME(l) = name;
  LNODE(l) = label;
  HNEXT(l) = next;
  return l;
}

//return the label NODE
NODE *get_label(LHASHNODE *in_hash[], char *name) {

  unsigned inti = hash(name);
  LHASHNODE *l = in_hash[i];

  while(l != NULL) {
    if (strcmp(name, HNAME(l))==0) {
      return LNODE(l);
    }
    l = HNEXT(l);
  }

  return NULL;

}

//saves the variabel's value
LHASHNODE *save(LHASHNODE *in_hash[], char *name, NODE *label) {

  unsigned int i = hash(name);
  LHASHNODE *l = in_hash[i];

  while(l!=NULL) {

    if (strcmp(name, HNAME(l))==0) {
      LNODE(l) = label;
      return l;
    }

    l = HNEXT(l);

  }

  l = new_lhashnode(name, label,in_hash[i]);

  return l;


}

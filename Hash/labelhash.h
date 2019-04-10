#ifndef LABELHASH_H
#define LABELHASH_H
#include "../LinkedList/linkedList.h"

#define LNODE(P)((P) -> label)


typedef struct lhashnode {
 char *name;
 NODE *label;
 struct lhashnode *next;
}LHASHNODE;


//----------------------------------------

LHASHNODE *new_lhashnode(char *name, NODE *label,int value, LHASHNODE *next);
NODE *get_label(LHASHNODE *in_hash[], char *name);
LHASHNODE *save(LHASHNODE *in_hash[], char *name, NODE *label);

//----------------------------------------

//LHASHNODE *labels[NHASH];

#endif

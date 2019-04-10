#ifndef VHASH_H
#define VHASH_H

#define VVALUE(P)((P) -> value)


typedef struct vhashnode {
 char *name;
 int value;
 struct vhashnode *next;
}VHASHNODE;


//----------------------------------------

HASHNODE *lookup(HASHNODE *in_hash[], char *name, int value, int create);
HASHNODE *new_hashnode(char *name, int value, HASHNODE *next);
void print(HASHNODE *in_hash[]);

//----------------------------------------

HASHNODE *Hashtable[NHASH];



#endif

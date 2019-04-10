#ifndef VHASH_H
#define VHASH_H

#define VVALUE(P)((P) -> value)


typedef struct vhashnode {
 char *name;
 int value;
 struct vhashnode *next;
}VHASHNODE;


//----------------------------------------

VHASHNODE *vsave(VHASHNODE *in_hash[], char *name, int value);
VHASHNODE *new_vhashnode(char *name, int value, VHASHNODE *next);
VHASHNODE *get_var(VHASHNODE *in_hash[], char *name);
void print(VHASHNODE *in_hash[]);

//----------------------------------------

// HASHNODE *Hashtable[NHASH];



#endif

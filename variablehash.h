#ifndef VHASH_H
#define HASH_H

#define HNAME(P)((P) -> name)
#define HVALUE(P)((P) -> value)
#define HNEXT(P)((P) -> next)

#define NHASH 4
#define MULTIPLICADOR 31


typedef struct hashnode {
 char *name;
 int value;
 struct hashnode *next;
}HASHNODE;


//----------------------------------------

unsigned int hash(char *str);
HASHNODE *lookup(HASHNODE *in_hash[], char *name, int value, int create);
HASHNODE *new_hashnode(char *name, int value, HASHNODE *next);
void print(HASHNODE *in_hash[]);

//----------------------------------------

HASHNODE *Hashtable[NHASH];



#endif

#ifndef HASH_H
#define HASH_H

#define NAME(P)((P) -> name)
#define VALUE(P)((P) -> value)
#define NEXT(P)((P) -> next)

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

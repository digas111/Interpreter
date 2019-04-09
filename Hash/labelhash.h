#ifndef LABELHASH_H
#define LABELHASH_H

#define LNAME(P)((P) -> name)
#define LVALUE(P)((P) -> value)
#define LNEXT(P)((P) -> next)

#define NHASH 4
#define MULTIPLICADOR 31


typedef struct llhashnode {
 char *name;
 NODE *label;
 struct llhashnode *next;
}LLHASHNODE;


//----------------------------------------

unsigned int hash(char *str);
HASHNODE *lookup(HASHNODE *in_hash[], char *name, int value, int create);
HASHNODE *new_hashnode(char *name, int value, HASHNODE *next);
void print(HASHNODE *in_hash[]);

//----------------------------------------

HASHNODE *Hashtable[NHASH];



#endif

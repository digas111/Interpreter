#ifndef HASH_H
#define HASH_H

#define NAME(P)((P) -> name)
#define VALUE(P)((P) -> value)
#define NEXT(P)((P) -> next)


typedef struct node {
 char *name;
 int value;
 struct node *next;
}NODE;


//----------------------------------------

unsigned int hash(char *str);
NODE *lookup(char *name, int value, int create);
NODE *new_node(char *name, int value, NODE *next);
void print();

//----------------------------------------



#endif

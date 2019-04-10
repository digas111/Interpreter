#include "../Instr/instr.h"

typedef struct node{
    Instr *instr;
    struct node *nxt;
}NODE;

#define INSTR(P)((P)->instr)
#define NXT(P)((P)->nxt)

NODE *lista_instr = NULL;


NODE *new_node(Instr *instr);
NODE *add_last(Instr *i, NODE *list);
void print_llist(NODE *list);
int length(NODE *list);
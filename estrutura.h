typedef enum {ATRIB, ADD, SUB, MUL, DIV, IF_I, PRINT, READ, GOTO_I, LABEL_I, QUIT_I} OpKind;

typedef enum {EMPTY, INT_CONST, STRING, LABEL, CONDITION, QUIT} ElemKind;

#include "hash.h"


#define KIND(P)((P)->op)

#define NAMECMD(P)((P)->first->contents.name)
#define VALCMD(P)((P)->second->contents.val)

typedef struct {
  ElemKind kind;
  union
   {
      int val;
      char *name;
    }contents;
} Elem;

typedef struct{
  OpKind op;
  Elem *first, *second, *third;
} Instr;


#define NXT(P)((P)->nxt)
#define INSTR(P)((P)->instr)

typedef struct node{
  Instr *instr;
  struct node *nxt;
}NODE;

NODE *new_node(Instr *i, NODE *prox);
int length(NODE *l);
void add_last(Instr *i);

//funcoes sobre instrucoes
Instr *new_instr(OpKind op, Elem *first, Elem *second, Elem *third);
Instr *instrfy(char *linha);


//funcoes sobre elements
Elem *new_elem(ElemKind k, char *n);
Elem *new_elem_int(ElemKind k, int v, char *n);
Elem *new_elem_string(ElemKind k, char *content, char *name);
Elem *new_elem_empty();


//funcoes run
void run_program();
void exec_instr(Instr *command);

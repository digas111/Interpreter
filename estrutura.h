typedef enum {ATRIB, ADD, SUB, MUL, DIV, IF_I, PRINT, READ, GOTO_I, LABEL_I, QUIT_I} OpKind;

typedef enum {EMPTY, INT_CONST, STRING, LABEL, CONDITION, QUIT} ElemKind;

#include "hash.h"

#define NXT(P)((P)->nxt)
#define INSTR(P)((P)->instr)
#define KIND(P)((P)->op)

#define NAMECMD(P)((P)->first->contents.inte.name)
#define VALCMD(P)((P)->second->contents.inte.val)

typedef struct {
  ElemKind kind;
  union{
   struct {
      int val;
      char *name;
    }inte;
    struct {
      char *content;
      char *name;
    }string;
  }contents;
} Elem;

typedef struct{
  OpKind op;
  Elem *first, *second, *third;
} Instr;

typedef struct node{
  Instr *instr;
  struct node *nxt;
}NODE;



//funcoes linked list
NODE *new_node(Instr *instruction);
int length(NODE *l); //retorna o tamanho da lista
//NODE *search(Instr instruction, NODE *l); //retorna o apontador para o nó que tem x(1ªocorrência)
NODE *add_last(Instr *instruction, NODE *l); // coloca novo nó no fim da lista
void print_lista(NODE *lista);

//funcoes sobre instrucoes
Instr *new_instr(OpKind op, Elem *first, Elem *second, Elem *third);
Instr *instrfy(char *linha);


//funcoes sobre elements
Elem *new_elem(ElemKind k, char *n);
Elem *new_elem_int(ElemKind k, int v, char *n);
Elem *new_elem_string(ElemKind k, char *content, char *name);
Elem *new_elem_empty();


//funcoes run
void run_program(NODE *lista);
void exec_instr(Instr *command);

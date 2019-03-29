typedef enum {ATRIB, ADD, SUB, MUL, IF_I, PRINT, READ, GOTO_I, LABEL} OpKind;

typedef enum {EMPTY, INT_CONST, STRING} ElemKind;

//#define
#define NXT(P)((P)->nxt)

typedef struct {
  ElemKind kind;
  union{
   struct {
      int val;
      char *name;
    }int;
    struct {
      int *p;
      char *name;
    }label;
    struct {
      char *content;
      char *name;
    }string; 
  }contents;
  
} Elem;

typedef struct{
  OpKind op;
  Elem first, second, third;
} Instr;

typedef struct node{
  Instr *instr;
  struct node *nxt;
}NODE;


NODE *new_node(Instr *instruction, NODE *prox);
int length(NODE *l); //retorna o tamanho da lista
//NODE *search(Instr instruction, NODE *l); //retorna o apontador para o nó que tem x(1ªocorrência)
NODE *add_last(Instr *instruction, NODE *l); // coloca novo nó no fim da lista

Instr *new_instr(Opkind op, Elem first, Elem second, Elem third);

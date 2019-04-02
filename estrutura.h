typedef enum {ATRIB, ADD, SUB, MUL, IF_I, PRINT, READ, GOTO_I} OpKind;

typedef enum {EMPTY, INT_CONST, STRING, LABEL} ElemKind;

#define NXT(P)((P)->nxt)

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
  Elem first, second, third;
} Instr;

typedef struct node{
  Instr *instr;
  struct node *nxt;
}NODE;

//funcoes linked list
NODE *new_node(Instr *instruction, NODE *prox);
int length(NODE *l); //retorna o tamanho da lista
//NODE *search(Instr instruction, NODE *l); //retorna o apontador para o nó que tem x(1ªocorrência)
NODE *add_last(Instr *instruction, NODE *l); // coloca novo nó no fim da lista

//funcoes sobre instrucoes
Instr *new_instr(OpKind op, Elem first, Elem second, Elem third);

//funcoes sobre elements
Elem *new_elem_int(ElemKind k, int v, char *n);
Elem *new_elem_string(ElemKind k, char *content, char *name);

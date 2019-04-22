#ifndef HASH_H
#define HASH_H
#include "instr.h"
#include "linkedlist.h"

#define NAME(P) ((P)->name)
#define NEXT(P) ((P)->next)
#define IVALUE(P) ((P)->data.ivalue)
#define FVALUE(P) ((P)->data.fvalue)
#define LABEL(P) ((P)->data.label)
#define KIND(P) ((P)->kind)

union hash {
  int ivalue;
  float fvalue;
  NODE *label;
};

typedef struct hashnode {
  ElemKind kind;
  char *name;
  struct hashnode *next;
  union hash data;
} HASHNODE;

//________________________________________

#define NHASH 4
#define MULTIPLICADOR 31

//________________________________________

//retorna o indice da hashtable em que o elemneto deve ser guardado
unsigned int hash(char *str);

//retorna o hashnode cujo nomo corresponde ao do Elem recebido
HASHNODE *get(HASHNODE *hashtable[], Elem e);
//guarda na hashtable a informação do elemnto recebido assim como os dados da union hash recebida
HASHNODE *save(HASHNODE *hashtable[], Elem e, union hash data);

/*        Auxiliares do save       */
//guarda no hashnode a informação contida na union hash que recebe
HASHNODE *setdata(HASHNODE *l, union hash data);
//cria um novo nó na hash com a informação do Elem recebido e com os dados da union hash recebida
HASHNODE *new_hashnode(Elem e, union hash data, HASHNODE *next);
/*                                 */

//imprime a ashtable que recebe como argumento
void print_hash(HASHNODE *hashtable[]);
//imprime o hashnode que recebe como argumento
void print_hashnode(HASHNODE *l);

//----------------------------------------

#endif

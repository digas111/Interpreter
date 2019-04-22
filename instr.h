#ifndef INSTR_H
#define INSTR_H

//________________________________________

#define isIntConstElem1(P) ((P).elem1.kind == INT_CONST)
#define isFloatConstElem1(P) ((P).elem1.kind == FLOAT_CONST)
#define isIntConstElem2(P) ((P).elem2.kind == INT_CONST)
#define isFloatConstElem2(P) ((P).elem2.kind == FLOAT_CONST)
#define isIntConstElem3(P) ((P).elem3.kind == INT_CONST)
#define isFloatConstElem3(P) ((P).elem3.kind == FLOAT_CONST)

//________________________

#define ISINT(P) ((P).kind == INT_CONST || (P).kind == INT_VAR)
#define ISFLOAT(P) ((P).kind == FLOAT_CONST || (P).kind == FLOAT_VAR)

#define ELEMKIND(P) ((P).kind)
#define ELEMNAME(P) ((P).contents.name)
#define ELEMINT(P) ((P).contents.intval)
#define ELEMFLOAT(P) ((P).contents.fvalue)

#define INSTROP(P) ((P).op)
#define INSTREELEM1(P) ((P).elem1)
#define INSTREELEM2(P) ((P).elem2)
#define INSTREELEM3(P) ((P).elem3)

#define INSTREELEM1KIND(P) ((P).elem1.kind)
#define INSTREELEM2KIND(P) ((P).elem2.kind)
#define INSTREELEM3KIND(P) ((P).elem3.kind)

#define INSTREELEM1NAME(P) ((P).elem1.contents.name)
#define INSTREELEM2NAME(P) ((P).elem2.contents.name)
#define INSTREELEM3NAME(P)((P) . elem3.contents.name

#define INSTREELEM1INT(P) ((P).elem1.contents.intval)
#define INSTREELEM2INT(P) ((P).elem2.contents.intval)
#define INSTREELEM3INT(P) ((P).elem3.contents.intval)

#define INSTREELEM1FLOAT(P) ((P).elem1.contents.fvalue)
#define INSTREELEM2FLOAT(P) ((P).elem2.contents.fvalue)
#define INSTREELEM3FLOAT(P) ((P).elem3.contents.fvalue)

typedef enum { EMPTY,
               INT_VAR,
               INT_CONST,
               FLOAT_VAR,
               FLOAT_CONST,
               LABEL,
               VAR } ElemKind;

typedef enum { READ,
               PRINT,
               IF,
               GOTO,
               LABEL_I,
               QUIT,
               ADD,
               SUB,
               DIV,
               MUL,
               ATRIB,
               ERROR } OpKind;

typedef struct {
  ElemKind kind;
  union {
    char *name;
    int intval;
    float fvalue;
  } contents;
} Elem;

typedef struct {
  OpKind op;
  Elem elem1, elem2, elem3;
} Instr;

#define SIZEKEYW 11

//VARIAVEIS GLOBAIS

extern char *keywords[SIZEKEYW];

Elem new_elem(ElemKind k, char *n, int v, float f);    //cria um novo elemento
Instr new_instr(OpKind k, Elem e1, Elem e2, Elem e3);  //cria nova instrucao
Instr instrfy(char *line);                             //torna uma linha de codigo em instrucao

/*        Auxiliares do instrfy       */
Instr new_instr_RWL(char str[], OpKind opk, ElemKind elk, char delim1[], char delim2[]);  //instrucoes do tipo READ, PRINT E LABEL
Instr new_instr_if(char str[]);                                                           //instrucao IF
Instr new_instr_op(char str[], char op[], OpKind k);                                      //operacoes aritmeticas
Instr new_instr_atrib(char str[]);                                                        //atribuicoes
Elem is_number(char *token);                                                              //retorna um elemento do tipo var ou constante(int ou float)

void print_instr(Instr i);  //imprime uma instrucao
void print_elem(Elem e);    //imprime um elemento

#endif

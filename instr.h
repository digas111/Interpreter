#ifndef INSTR_H
#define INSTR_H

//________________________________________

#define DEBUG 1

//________________________________________

#define ELEMKIND(P)((P) . kind)
#define ELEMNAME(P)((P) . contents.name)
#define ELEMINT(P)((P) . contents.intval)
#define ELEMFLOAT(P)((P) . contents.fvalue)

#define INSTROP(P)((P) . op)
#define INSTREELEM1(P)((P) . elem1)
#define INSTREELEM2(P)((P) . elem2)
#define INSTREELEM3(P)((P) . elem3)

#define INSTREELEM1KIND(P)((P) . elem1.kind)
#define INSTREELEM2KIND(P)((P) . elem2.kind)
#define INSTREELEM3KIND(P)((P) . elem3.kind)

#define INSTREELEM1NAME(P)((P) . elem1.contents.name)
#define INSTREELEM2NAME(P)((P) . elem2.contents.name)
#define INSTREELEM3NAME(P)((P) . elem3.contents.name

#define INSTREELEM1INT(P)((P) . elem1.contents.intval)
#define INSTREELEM2INT(P)((P) . elem2.contents.intval)
#define INSTREELEM3INT(P)((P) . elem3.contents.intval)

#define INSTREELEM1FLOAT(P)((P) . elem1.contents.fvalue)
#define INSTREELEM2FLOAT(P)((P) . elem2.contents.fvalue)
#define INSTREELEM3FLOAT(P)((P) . elem3.contents.fvalue)


typedef enum {EMPTY, INT_VAR, INT_CONST, FLOAT_VAR, FLOAT_CONST, LABEL} ElemKind;
typedef enum {READ, PRINT, IF, GOTO, LABEL_I, QUIT, ADD, SUB, DIV, MUL, ATRIB, ERROR} OpKind;


typedef struct{
    ElemKind kind;
    union {
        char *name;
        int intval;
        float fvalue;
    }contents;
}Elem;

typedef struct{
    OpKind op;
    Elem elem1, elem2, elem3;
} Instr;

#define SIZEKEYW 10



//VARIAVEIS GLOBAIS

extern char *keywords[SIZEKEYW];

Elem new_elem(ElemKind k, char *n, int v, float f);
Instr new_instr(OpKind k, Elem e1, Elem e2, Elem e3);
Instr instrfy(char *line);

Instr new_instr_RWL(char str[], OpKind opk, ElemKind elk, char delim1[], char delim2[]);
Instr new_instr_if(char str[]);
Instr new_instr_op(char str[], char op[], OpKind k);
Instr new_instr_atrib(char str[]);
Elem is_number(char *token);
void print_instr(Instr i);
void print_elem(Elem e);

#endif

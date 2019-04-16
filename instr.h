#ifndef INSTR_H
#define INSTR_H

typedef enum {EMPTY, INT_VAR, INT_CONST, FLOAT_VAR, FLOAT_CONST, LABEL}ElemKind;

typedef enum {READ, PRINT, IF, GOTO, QUIT, ADD, SUB, DIV, MUL, ATRIB} OpKind;

union contents{
    char *name;
    int ivalue;
    float fvalue;
    };

typedef struct{
    ElemKind kind;
    union contents info;
}Elem;

typedef struct{
    OpKind op;
    Elem *elem1, *elem2, *elem3;
} Instr;

#define SIZEKEYW 10



//VARIAVEIS GLOBAIS

extern char *keywords[SIZEKEYW];

Elem *new_elem(ElemKind k, union contents data);
Instr *new_instr(OpKind k, Elem *e1, Elem *e2, Elem *e3);
Instr *instrfy(char *line);

#endif

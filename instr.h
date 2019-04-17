#ifndef INSTR_H
#define INSTR_H

#define DEBUG 1

typedef enum {EMPTY, INT_VAR, INT_CONST, FLOAT_VAR, FLOAT_CONST, LABEL} ElemKind;

typedef enum {READ, PRINT, IF, GOTO, LABEL_I, QUIT, ADD, SUB, DIV, MUL, ATRIB} OpKind;

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
    Elem *elem1, *elem2, *elem3;
} Instr;

#define SIZEKEYW 10



//VARIAVEIS GLOBAIS

extern char *keywords[SIZEKEYW];

Elem *new_elem(ElemKind k, char *n, int v, float f);
Instr *new_instr(OpKind k, Elem *e1, Elem *e2, Elem *e3);
Instr *instrfy(char *line);
void print_instr(Instr* i);

Instr* new_instr_RWL(char str[], OpKind opk, ElemKind elk, char delim1[], char delim2[]);
Instr* new_instr_if(char str[]);
Instr* new_instr_op(char str[], char op[], OpKind k);
Instr* new_instr_atrib(char str[]);
Elem *is_number(char *token);
void print_instr(Instr* i);
void print_elem(Elem* e);

#endif

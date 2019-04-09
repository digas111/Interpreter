typedef enum {READ, PRINT, IF, GOTO, LABEL, QUIT, ADD, SUB, DIV, MUL, ATRIB} OpKind;

typedef struct{
    OpKind op;
    char *elem1, *elem2, *elem3;
} Instr;

#define SIZEKEYW 10

#define DEBUG 1

//VARIAVEIS GLOBAIS

char *keywords[] = {".ler(", ".if", ".escrever(", ".goto", ".label", ".quit", "+", "-", "*", "/"};

Instr *new_instr(OpKind k,char *e1, char *e2, char *e3);
Instr *instrfy(char *line);
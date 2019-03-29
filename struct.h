typedef enum {ATRIB, ADD, SUB, MUL, IF_I, PRINT, READ, GOTO_I, LABEL} OpKind;

typedef enum {EMPTY, INT_CONST, STRING, POINTER} ElemKind;

typedef struct {
  ElemKind kind;
  union {
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

  } contents;
} Elem;

typedef struct {
  OpKind op;
  Elem first, second, third;
} Instr;

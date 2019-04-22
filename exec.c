#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exec.h"

void exec_list(NODE *lista_instr, HASHNODE *hashtable[]) {
  NODE *p;

  while (lista_instr != NULL) {
    switch (INSTROP(INSTR(lista_instr))) {
      case 0:  //READ
        exec_read(INSTR(lista_instr), hashtable);
        break;
      case 1:  //PRINT
        exec_print(INSTR(lista_instr), hashtable);
        break;
      case 2:  //IF
        p = exec_if(INSTR(lista_instr), hashtable);
        if (p != NULL) {
          lista_instr = p;
        }
        break;
      case 3:  //GOTO
        p = exec_goto(INSTR(lista_instr), hashtable);
        if (p != NULL) {
          lista_instr = p;
        }
        break;
      case 4:  //LABEL_I
        break;
      case 5:  //QUIT
        return;
      case 6:  //ADD
        exec_add(INSTR(lista_instr), hashtable);
        break;
      case 7:  //SUB
        exec_sub(INSTR(lista_instr), hashtable);
        break;
      case 8:  //DIV
        exec_div(INSTR(lista_instr), hashtable);
        break;
      case 9:  //MUL
        exec_mul(INSTR(lista_instr), hashtable);
        break;
      case 10:  //ATRIB
        exec_atrib(INSTR(lista_instr), hashtable);
        break;
      default:
        break;
    }
    lista_instr = NXT(lista_instr);
  }
}

void exec_read(Instr i, HASHNODE *hashtable[]) {
  float f;

  scanf("%f", &f);

  save_result(INSTREELEM1(i), hashtable, f);
}

void exec_print(Instr i, HASHNODE *hashtable[]) {
  if (INSTREELEM1KIND(i) == INT_CONST) {
    printf("%d\n", INSTREELEM1INT(i));

  }

  else if (INSTREELEM1KIND(i) == FLOAT_CONST) {
    printf("%f\n", INSTREELEM1FLOAT(i));

  }

  else {
    HASHNODE *h = get(hashtable, INSTREELEM1(i));

    if (KIND(h) == INT_VAR) {
      printf("%d\n", IVALUE(h));
    }

    else if (KIND(h) == FLOAT_VAR) {
      printf("%f\n", FVALUE(h));
    }
  }
}

NODE *exec_if(Instr i, HASHNODE *hashtable[]) {
  HASHNODE *h = get(hashtable, INSTREELEM1(i));
  HASHNODE *l = get(hashtable, INSTREELEM2(i));

  if (KIND(h) == INT_VAR && !IVALUE(h)) {
    return NULL;
  }

  else if (KIND(h) == FLOAT_VAR && !FVALUE(h)) {
    return NULL;
  }

  return LABEL(l);
}

NODE *exec_goto(Instr i, HASHNODE *hashtable[]) {
  HASHNODE *l = get(hashtable, INSTREELEM1(i));

  return LABEL(l);
}

float is_int(float a) {
  int c = a;

  if (a - c == 0) {
    return 1;
  }
  return 0;
}

float get_val(Elem e, HASHNODE *hashtable[]) {
  if (ELEMKIND(e) == INT_CONST) {
    return ELEMINT(e);
  }

  if (ELEMKIND(e) == FLOAT_CONST) {
    return ELEMFLOAT(e);
  }

  HASHNODE *h = get(hashtable, e);

  if (KIND(h) == INT_VAR) {
    return IVALUE(h);
  }

  return FVALUE(h);
}

void save_result(Elem e, HASHNODE *hashtable[], float r) {
  union hash data;

  if (is_int(r)) {
    data.ivalue = (int)r;
    ELEMKIND(e) = INT_VAR;
  }

  else {
    data.fvalue = r;
    ELEMKIND(e) = FLOAT_VAR;
  }

  save(hashtable, e, data);
}

void exec_add(Instr i, HASHNODE *hashtable[]) {
  float a = get_val(INSTREELEM2(i), hashtable);
  float b = get_val(INSTREELEM3(i), hashtable);

  float r = a + b;
  save_result(INSTREELEM1(i), hashtable, r);
}

void exec_sub(Instr i, HASHNODE *hashtable[]) {
  float a = get_val(INSTREELEM2(i), hashtable);
  float b = get_val(INSTREELEM3(i), hashtable);

  float r = a - b;
  save_result(INSTREELEM1(i), hashtable, r);
}

void exec_mul(Instr i, HASHNODE *hashtable[]) {
  float a = get_val(INSTREELEM2(i), hashtable);
  float b = get_val(INSTREELEM3(i), hashtable);

  float r = a * b;
  save_result(INSTREELEM1(i), hashtable, r);
}

void exec_div(Instr i, HASHNODE *hashtable[]) {
  float a = get_val(INSTREELEM2(i), hashtable);
  float b = get_val(INSTREELEM3(i), hashtable);

  float r = a / b;
  save_result(INSTREELEM1(i), hashtable, r);
}

void exec_atrib(Instr i, HASHNODE *hashtable[]) {
  float r = get_val(INSTREELEM2(i), hashtable);
  save_result(INSTREELEM1(i), hashtable, r);
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "read.h"

char* string_add_last(char string[], int *size, char c) {

  int n = *size;

  string = (char *) realloc(string,(n+1)*sizeof(char));

  string[n] = c;

  n++;

  *size = n;

  return string;

}

char* dell_spaces(char *input) {

  int i,j=0;

  char *output;

  output = (char *) malloc(j);

  for (i=0; input[i]!='\0'; i++) {

    if (input[i]!=' ') {
      output = (char *) realloc(output,j+1);
      output[j] = input[i];
      j++;
    }

  }

  return output;

}

NODE *file_to_llist(char file_name[], NODE *lista_instr, HASHNODE *hashtable[]) {

  FILE * code;
  code = fopen(file_name, "r");

  char c;

  int i=0;

  if (code) {
    while ((c = getc(code)) != EOF) {

      int flag = 0;

      if (c != '\n') {
        i++;

        char *line;
        int index = 0;
        line = (char *) malloc(index*sizeof(char));

        line = string_add_last(line,&index,'.');
        line = string_add_last(line,&index,c);

        while ((c = getc(code)) != ';') {

          if (c == '=') {
            flag = 1;
          }

          line = string_add_last(line,&index,c);

        }

        line = string_add_last(line,&index,'\0');

        if (flag) {
          line = dell_spaces(line);
        }

        printf("line %d: %s-\n", i,line);

        lista_instr = process_line(line, lista_instr, hashtable);


      }

    }
  }

  fclose(code);
  return lista_instr;

}

NODE *process_line(char *line,NODE *lista_instr, HASHNODE *hashtable[]) {
  printf("INICIO process_line\n");
  Instr new_instr = instrfy(line);
  printf("depois do instrfy\n" );
  lista_instr = add_last(lista_instr,new_instr);

  if (INSTROP(new_instr) == LABEL_I) {

    union hash data;
    data.label = last(lista_instr);

    save(hashtable,INSTREELEM1(new_instr),data);

  }

  return lista_instr;

}


void exec_list(NODE *lista_instr, HASHNODE *hashtable[]) {

  NODE *p;

  while(lista_instr != NULL){
    switch(INSTROP(INSTR(lista_instr))){
      case 0: //READ
        exec_read(INSTR(lista_instr), hashtable);
        break;
      case 1: //PRINT
        exec_print(INSTR(lista_instr), hashtable);
        break;
      case 2: //IF
        p = exec_if(INSTR(lista_instr), hashtable);
        printf("pos exec\n");
        if (p != NULL) {
          printf("if p\n");
          lista_instr = p;
          printf("change\n");
        }
        break;
      case 3: //GOTO
        p = exec_goto(INSTR(lista_instr), hashtable);
        if (p!=NULL) {
          lista_instr = p;
        }
        break;
      case 4: //LABEL_I
        //exec_label(INSTR(lista_instr), hashtable);
        break;
      case 5: //QUIT
        return;
      case 6: //ADD
      case 7: //SUB
      case 8: //DIV
      case 9: //MUL
        exec_add(INSTR(lista_instr), hashtable);
        break;
      case 10: //ATRIB
        //exec_conta(INSTR(lista_instr), hashtable);
        break;
      default:
      break;
    }
    lista_instr = NXT(lista_instr);
    printf("next\n");
  }
}

void exec_read(Instr i, HASHNODE *hashtable[]) {

  char token[VARSIZE];

  scanf("%s", token);

  save(hashtable,INSTREELEM1(i),var(token));

}

void exec_print(Instr i, HASHNODE *hashtable[]) {

  printf("INICIIO exec_print\n" );

  if (INSTREELEM1KIND(i) == INT_CONST) {
    printf("const\n");

    printf("%d\n", INSTREELEM1INT(i));

  }

  else if (INSTREELEM1KIND(i) == FLOAT_CONST) {

    printf("%f\n", INSTREELEM1FLOAT(i));

  }

  else {

    HASHNODE *h =  get(hashtable,INSTREELEM1(i));

    if (INSTREELEM1KIND(i) == INT_VAR) {

      printf("%d\n", IVALUE(h));

    }

    else if (INSTREELEM1KIND(i) == FLOAT_VAR) {

      printf("%f\n", FVALUE(h));

    }

  }

}

NODE *exec_if(Instr i, HASHNODE *hashtable[]) {

  printf("execif\n");

  HASHNODE *h = get(hashtable,INSTREELEM1(i));
  HASHNODE *l = get(hashtable,INSTREELEM2(i));

  printf("hashnode\n");

  if (INSTREELEM1KIND(i) == INT_VAR && !IVALUE(h)) {
    printf("here\n");
    return NULL;
  }

  else if (INSTREELEM1KIND(i) == FLOAT_VAR && !FVALUE(h)) {
    printf("else\n");
    return NULL;
  }

  printf("pos if\n");

  return LABEL(l);

}

NODE *exec_goto(Instr i, HASHNODE *hashtable[]) {

  HASHNODE *l = get(hashtable,INSTREELEM1(i));

  return LABEL(l);

}




int get_int(Elem e, HASHNODE *hashtable[]) {

  if (ELEMKIND(e)==INT_CONST) {
    return ELEMINT(e);
  }

  return IVALUE(get(hashtable,e));

}

float get_float(Elem e, HASHNODE *hashtable[]) {

  if (ELEMKIND(e)==FLOAT_CONST) {
    return ELEMFLOAT(e);
  }

  return FVALUE(get(hashtable,e));

}


void exec_add(Instr i, HASHNODE *hashtable[]) {

  union hash data;

  if (ISINTELEM2(i) && ISINTELEM3(i)) {
    int a = get_int(INSTREELEM2(i),hashtable);
    int b = get_int(INSTREELEM3(i),hashtable);
    data.ivalue = a+b;
    set_kind(INSTREELEM1(i),INT_VAR);
  }

  else {

    int ia = 0;
    int ib = 0;
    float fa = 0;
    float fb = 0; 

    if (ISFLOATELEM2(i)) {
      fa = get_float(INSTREELEM2(i),hashtable);
    }
    else {
      ia = get_int(INSTREELEM2(i),hashtable);
    }

    if (ISFLOATELEM3(i)) {
      fb = get_float(INSTREELEM3(i),hashtable);
    }

    else {
      ib = get_int(INSTREELEM3(i),hashtable);
    }

    data.fvalue = fa + (float)ia + fb + (float)ib;
    set_kind(INSTREELEM1(i),FLOAT_VAR);
    
  }

  save(hashtable,INSTREELEM1(i),data);

}





union hash var(char *token) {

  union hash data;
  float f;

  if ((strstr(token,".")!=NULL || strstr(token,",")!=NULL) && (f = atof(token)) != 0.0) {
    data.fvalue = f;
    return data;
  }

  else {
    data.ivalue = atoi(token);
  }

  return data;

}

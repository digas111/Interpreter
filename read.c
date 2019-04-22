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

        //line = string_add_last(line,&index,'.');
        line = string_add_last(line,&index,c);

        while ((c = getc(code)) != ';') {

          if (c == '=') {
            flag = 1;
          }

		  if (c == ',') {
			  c = '.';
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
  Instr new_instr = instrfy(line);
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
        if (p != NULL) {
          lista_instr = p;
        }
        break;
      case 3: //GOTO
        p = exec_goto(INSTR(lista_instr), hashtable);
        if (p!=NULL) {
          lista_instr = p;
        }
        break;
      case 4: //LABEL_I
        break;
      case 5: //QUIT
        return;
      case 6: //ADD
        exec_add(INSTR(lista_instr), hashtable);
      break;
      case 7: //SUB
        exec_sub(INSTR(lista_instr), hashtable);
      break;
      case 8: //DIV
        exec_div(INSTR(lista_instr), hashtable);
      break;
      case 9: //MUL
        exec_mul(INSTR(lista_instr), hashtable);
      break;
      case 10: //ATRIB
        exec_atrib(INSTR(lista_instr), hashtable);
        break;
      default:
      break;
    }
    lista_instr = NXT(lista_instr);
  }
}

void exec_read(Instr i, HASHNODE *hashtable[]) {

  char token[VARSIZE];

  scanf("%s", token);

  save(hashtable,INSTREELEM1(i),var(token));

}

void exec_print(Instr i, HASHNODE *hashtable[]) {

  if (INSTREELEM1KIND(i) == INT_CONST) {
    printf("%d\n", INSTREELEM1INT(i));

  }

  else if (INSTREELEM1KIND(i) == FLOAT_CONST) {
    printf("%f\n", INSTREELEM1FLOAT(i));

  }

  else {

    HASHNODE *h =  get(hashtable,INSTREELEM1(i));

    if (KIND(h) == INT_VAR) {
      printf("%d\n", IVALUE(h));

    }

    else if (KIND(h) == FLOAT_VAR) {
      printf("%f\n", FVALUE(h));

    }

  }

}

NODE *exec_if(Instr i, HASHNODE *hashtable[]) {

  printf("execif\n");

  HASHNODE *h = get(hashtable,INSTREELEM1(i));
  HASHNODE *l = get(hashtable,INSTREELEM2(i));

  if (KIND(h) == INT_VAR && !IVALUE(h)) {
    return NULL;
  }

  else if (KIND(h) == FLOAT_VAR && !FVALUE(h)) {
    return NULL;
  }

  return LABEL(l);

}

NODE *exec_goto(Instr i, HASHNODE *hashtable[]) {

  HASHNODE *l = get(hashtable,INSTREELEM1(i));

  return LABEL(l);

}

float is_int(float a) {
  int c = a;

  if (a-c==0) {
    return 1;
  }
  return 0;
}




int get_int(Elem e, HASHNODE *hashtable[]) {

  if (ELEMKIND(e)==INT_CONST) {
    return ELEMINT(e);
  }

  HASHNODE *h = get(hashtable,e);

  if (KIND(h) == INT_VAR) {

    return IVALUE(h);

  }

  return 0;

}

float get_float(Elem e, HASHNODE *hashtable[]) {

  if (ELEMKIND(e)==FLOAT_CONST) {
    return ELEMFLOAT(e);
  }

  if (ELEMKIND(e)==INT_CONST) {
    return 0;
  }

  HASHNODE *h = get(hashtable,e);

  if (KIND(h) == FLOAT_VAR) {

    return IVALUE(h);

  }

  return 0;

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

  union hash data;

  int ia = get_int(INSTREELEM2(i),hashtable);
  int ib = get_int(INSTREELEM3(i),hashtable);
  float fa = get_float(INSTREELEM2(i),hashtable);
  float fb = get_float(INSTREELEM3(i),hashtable);

  float r = ((float)ia + fa) + ((float)ib + fb);

  if (is_int(r)) {
    data.ivalue = (int)r;
    INSTREELEM1KIND(i) = INT_VAR;
  }

  else {
    data.fvalue = r;
    INSTREELEM1KIND(i) = FLOAT_VAR;
  }

  save(hashtable,INSTREELEM1(i),data);
}

void exec_sub(Instr i, HASHNODE *hashtable[]) {

    union hash data;

  int ia = get_int(INSTREELEM2(i),hashtable);
  int ib = get_int(INSTREELEM3(i),hashtable);
  float fa = get_float(INSTREELEM2(i),hashtable);
  float fb = get_float(INSTREELEM3(i),hashtable);

  float r = ((float)ia + fa) - ((float)ib + fb);

  if (is_int(r)) {
    data.ivalue = (int)r;
    INSTREELEM1KIND(i) = INT_VAR;
  }

  else {
    data.fvalue = r;
    INSTREELEM1KIND(i) = FLOAT_VAR;
  }

  save(hashtable,INSTREELEM1(i),data);

}


void exec_mul(Instr i, HASHNODE *hashtable[]) {

  union hash data;

  int ia = get_int(INSTREELEM2(i),hashtable);
  int ib = get_int(INSTREELEM3(i),hashtable);
  float fa = get_float(INSTREELEM2(i),hashtable);
  float fb = get_float(INSTREELEM3(i),hashtable);

  float r = ((float)ia + fa) * ((float)ib + fb);

  if (is_int(r)) {
    data.ivalue = (int)r;
    INSTREELEM1KIND(i) = INT_VAR;
  }

  else {
    data.fvalue = r;
    INSTREELEM1KIND(i) = FLOAT_VAR;
  }

  save(hashtable,INSTREELEM1(i),data);

}

void exec_div(Instr i, HASHNODE *hashtable[]) {

  union hash data;

  int ia = get_int(INSTREELEM2(i),hashtable);
  int ib = get_int(INSTREELEM3(i),hashtable);
  float fa = get_float(INSTREELEM2(i),hashtable);
  float fb = get_float(INSTREELEM3(i),hashtable);

  float r = ((float)ia + fa) / ((float)ib + fb);

  if (is_int(r)) {
    data.ivalue = (int)r;
    INSTREELEM1KIND(i) = INT_VAR;
  }

  else {
    data.fvalue = r;
    INSTREELEM1KIND(i) = FLOAT_VAR;
  }

  save(hashtable,INSTREELEM1(i),data);

}

void exec_atrib(Instr i, HASHNODE *hashtable[]) {

  union hash data;

  if (INSTREELEM2KIND(i)==INT_CONST) {
    data.ivalue = INSTREELEM2INT(i);
    INSTREELEM1KIND(i) = INT_VAR;
  }

  else {
    data.fvalue = INSTREELEM2FLOAT(i);
    INSTREELEM1KIND(i) = FLOAT_VAR;
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

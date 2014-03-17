#include<stdio.h>
#include<stdlib.h>
//#include "threads.h"

typedef struct informacao{
  int m[9][9];
  int linha;
  int coluna;
  int numero;
}info;

void verificacao(int m[9][9]);
void imprime2(info param);
void *verificaLinhaThread(void *inf);
void *verificaColunaThread(void *inf);
void *verificaBlocoThread(void *inf);

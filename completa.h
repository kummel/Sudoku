#include<stdio.h>
#include<stdlib.h>
#include "dica.h"

typedef struct data_thread{
  int m[9][9];
  int linha, coluna;
}data_thread;

void completa(int m[9][9]);
int certificaCompleto();
void verificaUnico();
void completaUnico(int m[9][9]);
int verificaPossivel();

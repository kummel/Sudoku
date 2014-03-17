#include<stdlib.h>
#include<stdio.h>

typedef struct data_info{
  int valor;
  int pos[9];
  int linha, coluna;
  int unico;
}data;

typedef struct data_verif{
  int m[9][9];
  int poss[9];
  int linha, coluna;
}verifica;

void dica(int m[9][9], int imprime);
void iniciaDica(int m, data info);
void possibilidade(data in[9][9], int m[9][9], int linha, int coluna);
void *linhas(void *inf);
void *colunas(void *inf);
void *blocos(void *inf);
int verificaHaDica(int i, int j);
void imprimeDica();
data retornaStruct(int linha, int coluna);

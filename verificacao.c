#include "verificacao.h"

void verificacao(int m[9][9]){
  int i, j, k;
  int linha=0, coluna=0, numero=0;
  info parametro, parametro2, parametro3;
  pthread_t thr_lin[81], thr_col[81], thr_bloco[81];
  
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      parametro.m[i][j]=m[i][j];
      parametro2.m[i][j]=m[i][j];
      parametro3.m[i][j]=m[i][j];
    }
  }
  // imprime2(parametro);
  //verifica a linha
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      parametro.linha=i;
      parametro.coluna=j;
      parametro.numero=m[i][j];
      if (pthread_create(&thr_lin[k], NULL, verificaLinhaThread, (void *) &parametro))
	fprintf(stderr, "Erro na criacao da thread. \n");
      k++;
    }
  }
  
  //  for (i = 0; i < 81; i++) 
  //    pthread_join(thr_lin[i], NULL); 

  //verifica a coluna
  //  imprime2(parametro2);
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      parametro2.linha=i;
      parametro2.coluna=j;
      parametro2.numero=m[i][j];
      if (pthread_create(&thr_col[k], NULL, verificaColunaThread, (void *) &parametro2))
	fprintf(stderr, "Erro na criacao da thread. \n");
      k++;
    }
  }

  //  for (i = 0; i < 81; i++) 
  //    pthread_join(thr_col[i], NULL); 

  //verifica o bloco
  //imprime2(parametro3);
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      parametro3.linha=i;
      parametro3.coluna=j;
      parametro3.numero=m[i][j];
      if (pthread_create(&thr_bloco[k], NULL, verificaBlocoThread, (void *) &parametro3))
      	fprintf(stderr, "Erro na criacao da thread. \n");
      k++;
    }
  }

  // for (i = 0; i < 81; i++) 
  //   pthread_join(thr_bloco[i], NULL);
}

void imprime2(info param){
  int i,j;
  printf("\n\n\n");
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      printf("%d ", param.m[i][j]);
    }
    printf("\n");
  }
  printf("\n\n\n");
}

void *verificaLinhaThread(void *inf){
  int i, coluna, linha;
  info *in = (info*)inf;
  //printf("Esta verificando a linha %d\n", in->linha);
  coluna= in->coluna;
  linha= in->linha;

  for(i=0;i<9;i++){
    if(in->m[linha][i] == in->numero && coluna != i && in->numero !=
0){
      printf("O numero %d esta repetido na linha %d\n", in->numero, linha+1);
      pthread_exit(0);
    }else{
      //      pthread_exit(0);
    }
  }
  return NULL;
}

void *verificaColunaThread(void *inf){
  int i, coluna, linha;
  info *in = (info*)inf;
  //printf("Esta verificando a linha coluna %d\n", in->coluna);
  coluna= in->coluna;
  linha= in->linha;

  for(i=0;i<9;i++){
    if(in->m[i][coluna] == in->numero && linha != i && in->numero != 0){
      printf("O numero %d esta repetido na coluna %d\n", in->numero, coluna+1);
      pthread_exit(0);
    }else{
      //      pthread_exit(0);
    }
  }
  return NULL;
}

void *verificaBlocoThread(void *inf){
  int i, j,col_min, col_max, lin_min, lin_max;
  info *in = (info*)inf;
  int linha = in->linha;
  int coluna = in->coluna;

  if(in->coluna<3 && in->linha<3){
    lin_min=0;
    lin_max=3;
    col_min=0;
    col_max=3;
  }
  
  else if(in->coluna>2 && in->coluna<6 && in->linha<3){
    lin_min=0;
    lin_max=3;
    col_min=3;
    col_max=6;
  }

  else if(in->coluna>5 && in->linha<3){
    lin_min=0;
    lin_max=3;
    col_min=6;
    col_max=9;
  }
  
  else if(in->coluna<3 && in->linha>2 && in->linha<6){
    lin_min=3;
    lin_max=6;
    col_min=0;
    col_max=3;
  }

  else if(in->coluna>2 && in->coluna<6 && in->linha>2 && in->linha<6){
    lin_min=3;
    lin_max=6;
    col_min=3;
    col_max=6;
  }

   else if(in->coluna>5 && in->linha>2 && in->linha<6){
    lin_min=3;
    lin_max=6;
    col_min=6;
    col_max=9;
  }

  else if(in->coluna<3 && in->linha>5){
    lin_min=6;
    lin_max=9;
    col_min=0;
    col_max=3;
  }

  else if(in->coluna>2 && in->coluna<6 && in->linha>5){
    lin_min=6;
    lin_max=9;
    col_min=3;
    col_max=6;
  }

   else if(in->coluna>5 && in->linha>5){
    lin_min=6;
    lin_max=9;
    col_min=6;
    col_max=9;
  }

  for(i=lin_min;i<lin_max;i++){
     for(j=col_min;j<col_max;j++){
       if(in->m[i][j] == in->numero && in->numero != 0){
	 if(coluna != j || linha != i){
	   printf("O numero %d esta repetido na linha %d e coluna %d\n", in->numero, i+1, j+1);
	   pthread_exit(0);
	 }else{
	   //  pthread_exit(0);
	 }
       }
     }
   }

  return NULL;
}

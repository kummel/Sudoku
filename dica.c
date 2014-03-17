#include "dica.h"

data info[9][9];

void imprimeM(int m[9][9]){
  int i,j;
  printf("\n\n\n");
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

void dica(int m[9][9], int imprime){
  int i,j;
  data info2[9][9];
  
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      iniciaDica(m[i][j], info[i][j]);
      info[i][j].unico=0;
      info[i][j].linha=0;
      info[i][j].coluna=0;
    }
  }
  /*
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      info[i][j]=info2[i][j];
    }
  }
  */
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      int k=i,l=j;
      possibilidade(info, m, k,l);
    }
  }
    /*
      int k;
      for(k=0;k<9;k++){
      for(i=0;i<9;i++){
      printf("[%d][%d]=", k,i);
      for(j=0;j<9;j++){
      printf("%d ",info[k][i].pos[j]);
      }
      }
      printf("\n");
      }
    */
  if(imprime)
    imprimeDica();
}

void iniciaDica(int m,  data info){
  int h;
  info.valor=m;
  for(h=0;h<9;h++){
    info.pos[h]=0;
  }
}

void possibilidade(data in[9][9], int m[9][9], int linha, int coluna){
  int poss[9] = {1,2,3,4,5,6,7,8,9};
  int k,j;
  data info = in[linha][coluna];
  verifica parameter;
  pthread_t thr_lin[81], thr_col[81], thr_bloco[81];
  
  for(k=0;k<9;k++){
    for(j=0;j<9;j++){
      parameter.m[k][j]=m[k][j];
    }
  }

  for(k=0;k<9;k++){
    parameter.poss[k]=poss[k];
  }

  if(m[linha][coluna]==0){
    parameter.linha=linha;
    parameter.coluna=coluna;

    if (pthread_create(&thr_lin[k], NULL, linhas, (void *) &parameter))
      fprintf(stderr, "Erro na criacao da thread. \n");
    pthread_join(thr_lin[k], NULL); 
    
    if (pthread_create(&thr_col[k], NULL, colunas, (void *) &parameter))
      fprintf(stderr, "Erro na criacao da thread. \n");
    pthread_join(thr_col[k], NULL); 
    
    if (pthread_create(&thr_bloco[k], NULL, blocos, (void *) &parameter))
      fprintf(stderr, "Erro na criacao da thread. \n");
    pthread_join(thr_bloco[k], NULL); 

    k++;

    for(k=0;k<9;k++){
      info.pos[k]=parameter.poss[k];
      poss[k]=k+1;
    }
  }else{
    info.valor=m[linha][coluna];
  }
  info.linha=linha;
  info.coluna=coluna;
  in[linha][coluna]=info;
}

void *linhas(void *inf){
  int i, num;
  verifica *param = (verifica *)inf;
  for(i=0;i<9;i++){
    if(param->m[param->linha][i] != 0){
      num = param->m[param->linha][i];
      param->poss[num-1]=0;
    }
  }
}

void *colunas(void *inf){
  int i;
  verifica *param = (verifica *)inf;
  for(i=0;i<9;i++){
    if(param->m[i][param->coluna] != 0){
      param->poss[param->m[i][param->coluna]-1]=0;
    }
  }
}

void *blocos(void *inf){
  int i, j,col_min, col_max, lin_min, lin_max;

  verifica *param = (verifica *)inf;
  int coluna = param->coluna;
  int linha = param->linha;

  if(coluna<3 && linha<3){
    lin_min=0;
    lin_max=3;
    col_min=0;
    col_max=3;
  }
  
  else if(coluna>2 && coluna<6 && linha<3){
    lin_min=0;
    lin_max=3;
    col_min=3;
    col_max=6;
  }

  else if(coluna>5 && linha<3){
    lin_min=0;
    lin_max=3;
    col_min=6;
    col_max=9;
  }
  
  else if(coluna<3 && linha>2 && linha<6){
    lin_min=3;
    lin_max=6;
    col_min=0;
    col_max=3;
  }

  else if(coluna>2 && coluna<6 && linha>2 && linha<6){
    lin_min=3;
    lin_max=6;
    col_min=3;
    col_max=6;
  }

   else if(coluna>5 && linha>2 && linha<6){
    lin_min=3;
    lin_max=6;
    col_min=6;
    col_max=9;
  }

  else if(coluna<3 && linha>5){
    lin_min=6;
    lin_max=9;
    col_min=0;
    col_max=3;
  }

  else if(coluna>2 && coluna<6 && linha>5){
    lin_min=6;
    lin_max=9;
    col_min=3;
    col_max=6;
  }

   else if(coluna>5 && linha>5){
    lin_min=6;
    lin_max=9;
    col_min=6;
    col_max=9;
  }

  for(i=lin_min;i<lin_max;i++){
     for(j=col_min;j<col_max;j++){
       if(param->m[i][j] != 0){
	  param->poss[param->m[i][j]-1]=0;
       }
     }
   }
}

void imprimeDica(){
  int i,j,k=0,h, l;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(verificaHaDica(i,j)){
	printf("(");
	for(h=0;h<9;h++){
	  if(info[i][j].pos[h]!= 0)
	    printf("%d", info[i][j].pos[h]);
	}
	printf(") ");
      }else{
	printf("%d ", info[i][j].valor);
      }
         if(!(i%9) && i!=0)
      printf("\n");
  }
      printf("\n");
    }
  }

int verificaHaDica(int i, int j){
  int l, retorno=0;
  for(l=0;l<9;l++){
    if(info[i][j].pos[l] != 0){
      return 1;
    }
  }
  return 0;
}

data retornaStruct(int linha, int coluna){
  return info[linha][coluna];
}

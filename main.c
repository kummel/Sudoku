#include "main.h"
//#include "dica.h"

int main(){
  int m[9][9];
  int entradaValida = 0;
  char opt;

  inicia(m);
  printf("Primeiro entre com o tabuleiro\n");
  entradaValida = leitura(m);
  //imprime(m);

  while(entradaValida){
    printf("Entrada invalida, recomece!!\n");
    entradaValida = leitura(m);
  }
  
  printf("Agora escolha as opcoes:\nC-> Completa o diagrama\nD-> Dicas\nV-> Verifica o diagrama\nS-> Termina o programa\n");
  
  entradaValida=1;
  
  //scanf("\n", &opt);

  while(entradaValida){
    
    scanf("%c", &opt);
    switch(opt){
    
    case 'C': case 'c':
      completa(m);
      imprime(m);
      break;
    
    case 'D': case 'd':
      dica(m, 1);
      break;
    
    case 'V': case 'v':
      verificacao(m);
      break;
    
    case 'S': case 's':
      entradaValida = 0;
      break;
      
    case '\n':
      break;
      
    default:
      printf("Entrada invalida!\n");
      break;
      
    }
  }

  return 0;
}

void inicia(int m[9][9]){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      m[i][j]=0;
    }
  }
}

int leitura(int m[9][9]){
  int i=0,j=0;
  char a;
  while(i<9){
    while(j<9){
      scanf("%c", &a);
      if(a>48 && a<=57){
	m[i][j]=a-48;
	j++;
      }else{
	if(a==88 || a==120){
	  j++;
	}else{
	  if(!(a==' ' || a=='\n')){
	  printf("%d", a);
	  return 1;
	  }
	}
      }
    }
    j=0;
    i++;
  }
  return 0;
}

void imprime(int m[9][9]){
  int i,j;
  printf("\n\n\n");
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

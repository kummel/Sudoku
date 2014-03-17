#include "completa.h"

data info[9][9];

void completa(int m[9][9]){
  int i,j,k;
  int completo = 1;
 
  dica(m, 0);
  verificaUnico();
  if(verificaPossivel()){
    printf("SUDOKU impossivel!\n");
    exit(0);
  }
  while(completo){  

    for(i=0;i<9;i++){
      for(j=0;j<9;j++){
	info[i][j]=retornaStruct(i, j);
      }
    }
    
    completo=certificaCompleto();
    if(completo){
      completaUnico(m);
      dica(m,0);
      
      for(i=0;i<9;i++){
	for(j=0;j<9;j++){
	  iniciaDica(m[i][j], info[i][j]);
	  info[i][j].unico=0;
	}
      }
      
      for(i=0;i<9;i++){
	for(j=0;j<9;j++){
	  info[i][j]=retornaStruct(i, j);
	}
      }
      
      verificaUnico();
      if(verificaPossivel()){
	printf("SUDOKU impossivel!\n");
	exit(0);
      }
    }
  }
}

int verificaPossivel(){
  int i,j, possibilidade=0;
  
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(info[i][j].unico==0){
	possibilidade++;
      }else{
	
      }
    }
  }
  
  if(possibilidade==81)
    return 1;
  
  return 0;
}

int certificaCompleto(){
  int i,j;
  int completo=0;
  
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(info[i][j].valor==0)
	completo++;
    }
  }

  if(completo == 0)
    return 0;
  return 1;
}

void verificaUnico(){
  int i,j, k, numPos=0;
  
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      for(k=0;k<9;k++){
	if(info[i][j].pos[k] != 0){
	  numPos++;
	}
      }
      if(numPos==1){
	info[i][j].unico=1;
      }
      numPos=0;
    }
  }
}

void completaUnico(int m[9][9]){
  int i, j, k;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(info[i][j].unico == 1 && m[i][j] == 0){
	for(k=0;k<9;k++){
	  if(info[i][j].pos[k] != 0){
	    m[info[i][j].linha][info[i][j].coluna]=info[i][j].pos[k];
	    info[i][j].unico=0;
	    //info[i][j].pos[k]=0;
	  }
	}
      }
    }
  }
}

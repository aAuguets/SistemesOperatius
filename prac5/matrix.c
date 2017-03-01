#include <stdio.h>
#include <stdint.h>
#include "matrix.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void save_matrix(const char filename[],const matrix m){
  
  FILE *f;
  int i,j;
  
  f=fopen(filename,"w");
  if (f==NULL){
    perror("matrix");
  }
  else{
    printf("Guardant matriu a %s...\n", filename);
    for(i=0;i<DIM;i++){
      for(j=0;j<DIM;j++){
	if( j<DIM-1)
	  fprintf(f, "%.4f,", m[i][j]);
	else
	  fprintf(f,"%.4f",m[i][j]);
      }
      fprintf(f, "\n");
    }
  }
  fclose(f);
}

void load_matrix(const char filename[], matrix m){
    FILE *f;
    int i,j;
    f=fopen(filename,"r");
    printf("Obrint matriu %s ...\n", filename);
    if(f==NULL){
      perror("matrix");
    }else{
      for(i=0; i<DIM; i++){
	for(j=0; j<DIM; j++){
	  if(j == DIM-1){
	    fscanf(f, "%f\n", &m[i][j]);
	  }else{
	    fscanf(f, "%f,", &m[i][j]);
	  }
	}
      }
    }
    fclose(f);
    
  }


void print_matrix(const matrix a){
  printf("Matriu: \n");
  for (int i=0;i<DIM;i++){
    for(int x=0;x<DIM;x++){
      printf("%.2f\t",a[i][x]);
    }
    printf("\n");
  }
  printf("\n");
}

void const_matrix(matrix m, float v){
  for(int i=0;i<DIM;i++){
    for (int x=0;x<DIM;x++){
      m[i][x]=v;
    }
  }
}
void prod_matrix(const matrix a, const matrix b, matrix r, int minf, int maxf, int minc, int maxc){
  for (int i=minf;i<maxf;i++){
    for (int x=minc;x<maxc;x++){
      for (int n=0;n<DIM;n++){
	r[i][x]+=a[i][n]*b[n][x];
      }
    }
  }
}  

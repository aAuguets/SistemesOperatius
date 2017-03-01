#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


void escriu_ins(FILE *pipe ){
  fprintf(pipe, "set grid\n");
  fflush(pipe);
  fprintf(pipe, "set xlabel 'Agrupacions'\n");
  fflush(pipe);
  fprintf(pipe, "set ylabel 'Vots'\n");
  fflush(pipe);
  fprintf(pipe, "set style data histogram\n");
  fflush(pipe);
  fprintf(pipe, "set style fill solid border\n");
  fflush(pipe);
  fprintf(pipe, "set boxwidth 2\n");
  fflush(pipe);
  fprintf(pipe, "plot 'votos.dat' using 2:xticlabels(1) title 'VOTS' lc rgb 'green'\n");
  fflush(pipe);
  
}

int main(void){
  FILE *file_gnu;
  //abrimos con poppen la gnuplot
  file_gnu = popen("gnuplot","w");
  
  if (!file_gnu)
    return (EXIT_FAILURE);
  fflush(file_gnu);
  //ejecutamos la funcion dibuja que hace el dibujo 
  // mediante instrucciones gnuplot
  escriu_ins(file_gnu);
  while (true){
    fprintf(file_gnu,"replot\n");
    fflush(file_gnu);
    if(sleep(4) != 0)
      return (EXIT_FAILURE);
  }
  pclose(file_gnu);
  return 0;
}



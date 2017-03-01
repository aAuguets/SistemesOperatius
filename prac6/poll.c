#define _POSIX_C_SOURCE 200112L
#include "shrtbl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INST 1
#define PARTIT 2
#define VOTS 3



int main(int argc,char  const *argv[]){
  if (argc==0){
    perror("poll error");
  }
  //si se produce algun fallo en la comparticion de a tabla
  if(bin_shared_table() == ERR){
    puts("BIND,ERROR");
  }
  switch (argc){
  case 3: 
    //si leemos un new
    if(strcmp(argv[INST],"new")==0){
      if( add_party(argv[PARTIT])==ERR)
	fprintf(stderr,"No podem afegir el aprtit");
    }
    else if(strcmp(argv[INST],"del")==0){
      if(del_party(argv[PARTIT])==ERR)
	fprintf(stderr,"No podem treure el aprtit");
    }
    break;
  case 4:
    if(strcmp(argv[INST],"add")==0){
      if(inc_votes(argv[PARTIT],atoi(argv[VOTS]))==ERR)
	fprintf(stderr,"No podem incremementar el vots del partit");
    }
    else if(strcmp(argv[INST],"del")==0){
      if(del_party(argv[PARTIT])==ERR)
	fprintf(stderr,"No podem treure el aprtit");
    }
    break;
    default:
      return ERR;
      break;
  }
  return EXIT_SUCCESS;
  
}

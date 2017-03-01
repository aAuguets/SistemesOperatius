#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>


int main(void){
  pid_t pid, pid_table[4];
  int i;

  for (i=0; i<4; i++){
    //provocant error quan i pren per valor 3.
    if(i==3)
      pid = -1;
    else{
      pid = fork();
    }

    switch(pid){
    case 0:
      printf("Soc el fill %d amb pid: %d\n",i, getpid());
      exit(0);
    
    case -1: 
      fprintf(stderr, "Error en crear el fill\n");
      while(i>0){
	kill(pid_table[i-1], SIGTERM);
	i--;
      }
      exit(EXIT_FAILURE);
    
  default:
      pid_table[i] = pid;
      printf("Pare, pid %d guardat a la posicio %d de taula.\n",pid_table[i],i);  
    }
  }
  printf("Fent wait\n");
  for(i=0;i<4;i++)
    wait(NULL);
  return 0;
}

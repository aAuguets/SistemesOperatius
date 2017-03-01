#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(void){
  pid_t pid, pid_table[4], wait_s;
  int i, status, proc = 0;
  char child_n[8]="child";
  char fill_n[2];
  
  for (i=0; i<4; i++){
    pid = fork();
    
    switch(pid){
    case 0:
      sprintf(child_n, "%s%d",child_n, i);//sirve para concatenar
      //printf("child_n -> %s\n",child_n);
      sprintf(fill_n, "%d", i);
      
      //printf("child_n -> %s\n",child_n);
      execlp("./child","child", child_n, "arbitrari", fill_n, NULL);
      //exit(0);
    
    case -1: 
      fprintf(stderr, "Error en crear el fill\n");
      while(i>0){
	kill(pid_table[i-1], SIGTERM);
	i--;
      }
      exit(EXIT_FAILURE);
    
  default:
      pid_table[i] = pid;
    }
  }

  wait_s = wait(&status);

  while(wait_s > 0){
    if(WIFEXITED(status))
      if(WEXITSTATUS(status) == EXIT_SUCCESS)
	proc ++;
    wait_s = wait(&status);
  }

  if(proc == 4){
    printf("EXIT_SUCCESS\n");
    exit(EXIT_SUCCESS);
  }
  else{
    printf("EXIT_FAILURE\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}

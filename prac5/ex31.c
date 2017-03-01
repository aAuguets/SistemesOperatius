#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void){
  pid_t pid, pid_table[4];
  int i;

  
  for (i=0; i<4; i++){
    pid = fork();
    if(pid == 0){
      printf("Soc el fill %d amb pid: %d\n",i, getpid());
      exit(0);
    }
    else if (pid == -1)
      printf("Error en crear el fill %d amb pid: %d\n", i, getpid());
    else{
      pid_table[i] = pid;
      printf("Pare, pid %d guardat a la posicio %d de taula.\n",pid_table[i],i);
    }
  }
  printf("Fent wait\n");
  for(i=0;i<4;i++)
    wait(NULL);
  return 0;
}

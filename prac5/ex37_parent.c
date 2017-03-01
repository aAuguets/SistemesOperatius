#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "matrix.h"
static void _unlink(void);

int main(void){
  pid_t pid, pid_table[4], wait_s;
  int i, status, proc = 0,fd,retVal_c,retVal_shm;//n
  void *addr; //n
  char child_n[8]="child";
  char fill_n[2];
  //ex 3.7: "Apunts sbs"
  fd = shm_open("parentMem", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
  if(fd == -1)
    exit(EXIT_FAILURE);
  if(ftruncate(fd, 3*SIZE) == -1)
    exit(EXIT_FAILURE);
  addr = mmap(NULL, 3*SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if(addr == MAP_FAILED)
    exit(EXIT_FAILURE);
  //4.
  retVal_c = close(fd);

  //6.
  if(retVal_c != 0){
    perror("ex37_parent");
    _unlink();
    exit(EXIT_FAILURE);
  }

  //5.
  matrix A = addr;
  matrix B = addr + SIZE;
  matrix R = addr + 2*SIZE;
  
  for (i=0; i<4; i++){
    pid = fork();
    
    switch(pid){
    case 0:
      sprintf(child_n, "%s%d",child_n, i);
      sprintf(fill_n, "%d", i);
      //7.
      execlp("./child","child", child_n, "parentMem", fill_n, NULL);
    
    case -1: 
      fprintf(stderr, "Error en crear el fill\n");
      while(i>0){
	kill(pid_table[i-1], SIGTERM);
	i--;
      }
      _unlink();
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

  if(proc != 4){
    printf("EXIT_FAILURE\n");
    //6.
    _unlink();
    exit(EXIT_FAILURE);
  }
  _unlink();
  printf("EXIT_SUCCESS\n");
  exit(EXIT_SUCCESS);
  return 0;
}

//6. funcio
/*
 *void _unlink(void);
 *La funcio realitza shm_unlink("parentMem") i 
 *comprova si el que ha retornat es correcte o no,
 *en cas negatiu realitza un exit(EXIT_FAILURE).
 */
void _unlink(void){
  int retVal_shm;
  retVal_shm = shm_unlink("parentMem");
  if(retVal_shm == -1){
    perror("ex37_parent");
    exit(EXIT_FAILURE);
  }
}

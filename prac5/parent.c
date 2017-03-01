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

int main(int argc, char *argv[]){
  pid_t pid, pid_table[4], wait_s;
  int i, status, proc = 0,fd,retVal_c,retVal_shm;//n
  void *addr; //n
  char child_n[8]="child";
  char fill_n[2];
  if (argc != 4)
    exit(EXIT_FAILURE);
  
  fd = shm_open("parentMem", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
  if(fd == -1)
    exit(EXIT_FAILURE);
  if(ftruncate(fd, 3*SIZE) == -1)
    exit(EXIT_FAILURE);
  addr = mmap(NULL, 3*SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if(addr == MAP_FAILED)
    exit(EXIT_FAILURE);
  
  retVal_c = close(fd);

  
  if(retVal_c != 0){
    perror("parent");
    _unlink();
    exit(EXIT_FAILURE);
  }

  
  matrix A = addr;
  matrix B = addr + SIZE;
  matrix R = addr + 2*SIZE;
  
  load_matrix(argv[1], A);
  load_matrix(argv[2], B);
  
  
  for (i=0; i<4; i++){
    pid = fork();
    
    switch(pid){
    case 0:
      sprintf(child_n, "%s%d",child_n, i);
      sprintf(fill_n, "%d", i);
  
      execlp("./child","child", child_n, "parentMem", fill_n, NULL);
      break;
    case -1: 
      fprintf(stderr, "Error en crear el fill\n");
      while(i>0){
	kill(pid_table[i-1], SIGTERM);
	i--;
      }
      _unlink();
      exit(EXIT_FAILURE);
      break;
  default:
      pid_table[i] = pid;
      break;
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
   
    _unlink();
    exit(EXIT_FAILURE);
  }
  _unlink();
  print_matrix(R);
  save_matrix(argv[3], R);
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
    perror("parent");
    exit(EXIT_FAILURE);
  }
}

#define _POSIX_C_SOURCE 200809L
/*
 * Exercici del pdf!!!! 
 */
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

#include "matrix.h"

int main(int argc, char *argv[]){
  int fd;
  void *addr;
  struct stat st;

  fd = shm_open(argv[2], O_RDWR,0); //el flag O_RDWR permet llegir i escriure.
  if(fd == -1)
    exit(EXIT_FAILURE);
  if(fstat(fd, &st) == -1)
    exit(EXIT_FAILURE);
  addr = mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if(addr == MAP_FAILED)
    exit(EXIT_FAILURE);

  //prog
  if (argc==4){
    matrix A = addr;
    matrix B = addr + SIZE;
    matrix R = addr + 2*SIZE;
    
    if(!strcmp(argv[1], "child0"))
      prod_matrix(A,B,R,0,DIM/2,0,DIM/2);
    else if(!strcmp(argv[1], "child1"))
      prod_matrix(A,B,R,0,DIM/2,DIM/2,DIM);
    else if(!strcmp(argv[1],"child2"))
      prod_matrix(A,B,R,DIM/2,DIM,0,DIM/2);
    else if(!strcmp(argv[1],"child3"))
      prod_matrix(A,B,R,DIM/2,DIM,DIM/2,DIM);
    else
      printf("error de parametres");
    
    exit(EXIT_SUCCESS);
  }
  else{
    exit(EXIT_FAILURE);
  }
  
  
  if(close(fd) == -1){
    perror("child");
    shm_unlink(argv[2]);
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
  return 0;
}

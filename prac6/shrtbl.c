#define _POSIX_C_SOURCE 200112L
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include "shrtbl.h"

static taula_partits *addr;
static taula_partits *partits_table;

#define SEM &(partits_table->mutex)

int create_shared_table(void){
  //S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
  int fd;
  fd = shm_open(MEM, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
  if(fd == -1)
    return ERR;
  if(ftruncate(fd, sizeof(partits_table)) == -1)
    return ERR;
  if(close(fd) == -1)
    return ERR;
  else 
    return OK;
}

int remove_shared_table(void){
  if (sem_destroy(SEM) == -1)
    return ERR;

  if(shm_unlink(MEM) == -1)
    return ERR;
  return OK;

}

int bind_shared_table(void){
  int fd;
  fd = shm_open(MEM, O_RDWR, 0);
  if(fd == -1)
    return ERR;

  addr = mmap(NULL, TABLE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  if(addr == MAP_FAILED)
    return ERR;

  partits_table = addr;
  if(sem_init(SEM,1,1)>0)
    return ERR;

  if(close(fd) == -1)
    return ERR;
  else 
    return OK;
}

void init_table(void){
  partits_table -> n_partits = 0;
  for (int i = 0; i < N_PARTITS; i++)
    partits_table -> partits[i].estat = false;
}

int add_party(const char id[]){
  sem_wait(SEM);
  if (partits_table -> n_partits >= N_PARTITS){
    return ERR;
    sem_post(SEM); //signal sem
    } 
  for (int i = 0;  i <= partits_table -> n_partits; i++){
    if(strncmp(partits_table->partits[i].n_partit, id, MAX)){
      sem_post(SEM);
      return ERR;
    }
    if(i == partits_table -> n_partits){
      partits_table -> partits[i].estat = false;
      strncpy(partits_table -> partits[i].n_partit, id, MAX);
      partits_table -> partits[i].n_vots = 0;
      partits_table -> n_partits++;
      break;
    }
    else if(partits_table -> partits[i].estat == false){
      partits_table -> partits[i].estat = false;//true??
      strncpy(partits_table -> partits[i].n_partit, id, MAX);
      partits_table -> partits[i].n_vots = 0;
      partits_table -> n_partits++;
      break;
    }
  }
  sem_post(SEM);
  return OK; 
}

void del_party(const char id[]){
  sem_wait(SEM);
  for(int i = 0; i < partits_table -> n_partits; i++){
    if (strncmp(partits_table->partits[i].n_partit, id, MAX) == 0)
      partits_table -> partits[i].estat = false;
    partits_table -> n_partits--;
  }
  sem_post(SEM);
}

void inc_votes(const char party[], int votes){
  sem_wait(SEM);
  for(int i =0; i < partits_table -> n_partits; i++){
    if (strncmp(partits_table -> partits[i].n_partit, party, MAX) == 0)
      partits_table -> partits[i].n_vots += votes;
  }
  sem_post(SEM);
}

int get_votes(const char party[]){
  int vots = ERR;
  sem_wait(SEM);
  for(int i = 0; i <= partits_table -> n_partits; i++){
    if(i == partits_table -> n_partits){
      sem_post(SEM);
      return ERR;
    }
    else if(strncmp(partits_table ->partits[i].n_partit, party, MAX) == 0){
      vots = partits_table -> partits[i].n_vots;
    }
  }
  sem_post(SEM);
  return vots;
}

int get_nparties(void){
  sem_wait(SEM);
  int total_partits;
  total_partits = partits_table -> n_partits;
  sem_post(SEM);
  return total_partits;
}

void traverse(travapp *const f, void *const data){
  sem_wait(SEM);
  for(int i = 0; partits_table -> n_partits; i++){
    if(partits_table -> partits[i].estat == true){
      f(partits_table -> partits[i].n_partit, partits_table -> partits[i].n_vots, data);
    }
  }
  sem_post(SEM);
}














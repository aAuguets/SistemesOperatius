#ifndef SHRTBL_H
#define SHRTBL_H

#include <stdbool.h>
#include <semaphore.h>

#define N_PARTITS 30
#define MAX 10
#define OK 0
#define ERR -1
#define MEM "mem_comp"
#define TABLE_SIZE sizeof(taula_partits)

typedef struct{
  bool estat;
  int n_vots;
  char n_partit[MAX];
} partit_s;


typedef struct{
  int n_partits;
  partit_s partits[N_PARTITS];
  sem_t mutex;    
} taula_partits;

typedef void travapp(const char *const id, int votes, void *const data);

int create_shared_table(void);
int remove_shared_table(void);
int bind_shared_table(void);

void init_table(void);
int add_party(const char id[]);
void del_party(const char id[]);
void inc_votes(const char party[], int votes);
int get_vote(const char party[]);
int get_nparties(void);
void traverse(travapp *const f ,void *const data);


#endif

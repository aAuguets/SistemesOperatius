#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[]){
  char *curr_dir = NULL;
  DIR *dp = NULL;
  struct dirent *dptr = NULL;
  unsigned int count = 0;

  curr_dir = getenv("PWD");
  if(NULL == curr_dir){
    printf("\nError: No s'ha pogut obtenir el directori de treball.\n");
    return -1;
  }
  if(!argv[1]){
    dp = opendir((const char*)curr_dir);
    if(NULL == dp){
      printf("\nError: No s'ha pogut obtenir el directori de treball.\n");
      return -1;
    }
    
    for(count = 0; NULL != (dptr = readdir(dp)); count++){
      if(dptr->d_name[0] != '.')
	printf("%s \n", dptr->d_name);
    }
  }
  else{
    dp = opendir(argv[1]);
    if(NULL == dp){
      printf("\nError: No s'ha pogut obtenir el directori de treball.\n");
      return -1;
    }
    
    for(count = 0; NULL != (dptr = readdir(dp)); count++){
      if(dptr->d_name[0] != '.')
	printf("%s \n", dptr->d_name);
    }
  }
}

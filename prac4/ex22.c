#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int check_dp(DIR *dp){
  if(NULL == dp){
    printf("\nError: No s'ha pogut obtenir el directori de treball.\n");
    return -1;
  }
}

int main(int argc, char* argv[]){
  char *curr_dir = NULL;
  DIR *dp = NULL;
  struct dirent *dptr = NULL;
  unsigned int count = 0;
  struct stat fileStat;
  int err;
  char path[255];

  curr_dir = getenv("PWD");
  if(NULL == curr_dir){
    printf("\nError: No s'ha pogut obtenir el directori de treball.\n");
    return -1;
  }
  
  if(!argv[1]){
    dp = opendir((const char*)curr_dir);
    check_dp(dp);
        
    while(NULL != (dptr = readdir(dp))) {
      if(dptr->d_name[0] != '.'){
	printf("%s\n", dptr->d_name);
	stat(dptr->d_name, &fileStat);
	printf("Diferencia de bytes ocupats fitxer: \t%lu bytes\n\n", (fileStat.st_blocks*512 - fileStat.st_size));
      }
    }
    closedir(dp);
  }
  else{
    dp = opendir(argv[1]);
    check_dp(dp);
    
    while(NULL != (dptr = readdir(dp))){
      if(dptr->d_name[0] != '.'){
	printf("%s \n", dptr->d_name);
	strcpy(path,argv[1]);
	strcat(path,"/");
	strcat(path,dptr->d_name);
	if (!stat(path, &fileStat))
	  printf("Diferencia de bytes ocupats fitxer: \t%ld bytes\n\n",((fileStat.st_blocks*512)-fileStat.st_size));
	else{
	  perror("ex22");
	  abort();
	}
      }
    }
    closedir(dp);
  }
}

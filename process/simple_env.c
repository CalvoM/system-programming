#include "utils.h"

extern char** environ;

int main(int argc,char** argv){
  clearenv();
  char** ep;
  int i=0;
  for (i=0;i<argc;i++){
    if(putenv(argv[i])!=0) errExit("Issue with %s",argv[i]);
  }
  printf("Setting new environment\n\r");
  int ret = setenv("VISUAL","SCREEN",1);
  if(ret!=0){
    printf("Erroring updating the environment");
  }
  printf("---------------------------------------------------\n\r");
  for(ep=environ;*ep!=NULL;ep++){
    puts(*ep);
  }
}
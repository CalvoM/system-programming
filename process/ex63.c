#include "utils.h"
extern char** environ;
int custom_set_env(const char* key,const char *value, int overwrite);
int custom_get_env(const char* key);
char* concatenate(const char* key,const char* value,const char* joiner);
int main(int argc,char** argv){
    clearenv();
    char** ep;
    custom_set_env("area","Ndumbuini",1);
    for(ep=environ;ep!=NULL;ep++){
      puts(*ep);
    }

}

int custom_set_env(const char* key,const char *value, int overwrite){
    char *curr_val = getenv(key);
    if(curr_val == NULL){
        char * res = concatenate(key,value,"=");
        int err = putenv(res);
        if(err!=0){
          return -1;
        }else{
          return 0;
        }
    }else if(curr_val !=NULL && overwrite>0){

    }else if(curr_val!=NULL && overwrite==0){ //Value present and no overwrite specified
      return 0;
    }
}
char* concatenate(const char* key,const char* value,const char* joiner){
    size_t k_len = strlen(key);;
    size_t v_len = strlen(value);
    size_t j_len = strlen(joiner);
    char * res = malloc(k_len+v_len+j_len+1);
    if (res){
        memcpy(res,key,k_len);
        memcpy(res+k_len,joiner,j_len);
        memcpy(res+k_len+j_len,value,v_len+1);
    }
    return res;
}
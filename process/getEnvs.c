#include "utils.h"
int main(){
    printf("%s\r\n",getenv("SHELL"));
    printf("%d\r\n",getpid());
}
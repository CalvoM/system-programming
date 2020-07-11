#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(){
    FILE *fd = fopen("./test.txt","r");
    strerror();
    perror("File open");
}
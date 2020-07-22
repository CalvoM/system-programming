#include <sys/uio.h>

#include "utils.h"
int main(int argc, char** argv[]){
    int fd;
    struct iovec iov[3];
    struct stat myStruct;
    int x;
    #define STR_SIZE 100
    char str[STR_SIZE];
    ssize_t numRead,totRequired;
    fd = open(argv[1],O_RDONLY);
    if(fd==-1){
        errExit("open");
    }
    totRequired=0;
    iov[0].iov_base = &myStruct;
    iov[0].iov_len = sizeof(struct stat);
    totRequired += iov[0].iov_len;
    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    totRequired+=iov[1].iov_len;
    iov[2].iov_base =str;
    iov[2].iov_len = STR_SIZE;
    totRequired+=iov[2].iov_len;
    numRead = readv(fd,iov,3);
    if(numRead ==-1){
        errExit("Readv");
    }
    if(numRead < totRequired){
        printf("Read fewer bytes than requested\n\r");
    }
    ssize_t percentage = ((float)numRead/(float)totRequired)*100;
    printf("Bytes Requested:%ld  Bytes Read:%ld %.2f% \n\r",(long)totRequired,(long)numRead,(float)percentage);
    exit(EXIT_SUCCESS);
}
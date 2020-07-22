#include "utils.h"

int main(int argc, char** argv){
    if(argc<3){
        errMsg("Exiting...");
    }
    int inputFd,outputFd,outputFlags;
    mode_t outputPerms;
    inputFd = open(argv[1],O_RDWR);
    if(inputFd==-1){
        errMsg("Open file descriptor error");
    }
    int flags = fcntl(inputFd,F_GETFL);
    printf("Flags %#x and %#x",flags&O_ACCMODE,O_ACCMODE);
    if(flags & O_SYNC){
        printf("Synchronization!!!");
    }
    close(inputFd);
}
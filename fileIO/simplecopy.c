#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char** argv){
    int inputFd,outputFd,openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if(argc != 3 || strcmp(argv[1],"--help")==0) usageErr("%s old-file new-file\n",argv[0]);
    inputFd = open(argv[1],O_RDONLY); //Open for reading alone
    if(inputFd == -1) errExit("opening file %s",argv[1]);
    openFlags = O_CREAT | O_WRONLY | O_TRUNC; //Create a file for write-only purpose and if it exists then overwrite
    filePerms = S_IRUSR | S_IWUSR  | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; //rw-rw-rw- UGO
    outputFd = open(argv[2],openFlags,filePerms);
    if(outputFd == -1) errExit("opening file %s",argv[2]);
    int ch_mod = fchmod(outputFd,filePerms); //Confirm that the permissions set is correct and exact
    if(ch_mod == -1) errExit("Setting modes failed");
    while((numRead = read(inputFd,buf,BUF_SIZE)) > 0) if(write(outputFd,buf,numRead) != numRead) fatal("Could not write whole buffer");
    if(numRead== -1) errExit("read");
    if(close(inputFd) == -1) errExit("close input file");
    if(close(outputFd) == -1) errExit("close output file");
    exit(EXIT_SUCCESS);
}


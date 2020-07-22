/**
 * cp-like program that can copy even sparse files correctly with null bytes
*/
#include "utils.h"
#define MAX_SIZE 1
int main(int argc, char** argv){
    int input_fd,output_fd,output_flags;
    char out_buf[MAX_SIZE];
    mode_t file_perms;
    if(argc!=3 || strcmp(argv[1],"--help")==0){
        usageErr("%s source destination",argv[0]);
    }
    input_fd = open(argv[1],O_RDONLY);
    if(input_fd == -1) {
        errExit("Error opening the source file");
    }
    output_flags = O_WRONLY | O_CREAT | O_TRUNC;
    file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    output_fd = open(argv[2],output_flags,file_perms);
    if(output_fd == -1) {
        errExit("Error opening the source file");
    }
    while(read(input_fd,out_buf,MAX_SIZE)){
        lseek(input_fd,1,SEEK_CUR);
        write(output_fd,out_buf,1);
    }
    close(output_fd);
    close(input_fd);
    printf("Copying from %s to %s",argv[1],argv[2]);
}
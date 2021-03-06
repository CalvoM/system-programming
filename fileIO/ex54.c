// Implement dup() and dup2() using fcntl() and, where necessary, close(). (You may
// ignore the fact that dup2() and fcntl() return different errno values for some error
// cases.) For dup2(), remember to handle the special case where oldfd equals newfd. In
// this case, you should check whether oldfd is valid, which can be done by, for example,
// checking if fcntl(oldfd, F_GETFL) succeeds. If oldfd is not valid, then the function
// should return –1 with errno set to EBADF .
#include "utils.h"

int my_dup(int oldfd){
    int fd = fcntl(oldfd,F_DUPFD_CLOEXEC,0);
    return fd;

}
int my_dup2(int old_fd, int new_fd){
    int status_flags = fcntl(old_fd,F_GETFL);
    if(status_flags==-1){
        errno=EBADF;
        return -1;
    }
    int status_flags_2 = fnctl(new_fd,F_GETFL);
    if(status_flags==status_flags_2){
        return new_fd;
    }
    
}
int main(int argc, char** argv){
    if(argc==1 || strcmp(argv[1],"--help")==0){
        usageErr("%s <pathname>",argv[0]);
    }
    int fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC);
    if(fd==-1){
        errExit("Opening file");
    }
    int dup_fd = my_dup(fd);
    if(dup_fd==-1){
        errExit("Error in duplicating the file descriptor");
    }
    write(dup_fd,"----",4);
    close(fd);
}
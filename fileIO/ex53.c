// This exercise is designed to demonstrate why the atomicity guaranteed by
// opening a file with the O_APPEND flag is necessary.Write a program that takes
// up to three command -line arguments :
//     $ atomic_append filename num-bytes[x]

// This file should open the specified filename(creating it if necessary) and
// append num - bytes bytes to the file by using write() to write a byte at a
// time.By default,the program should open the file with the O_APPEND flag, but
// if a third command - line argument(x) is supplied,then the O_APPEND flag
// should be omitted, and instead theshould perform an lseek(fd, 0, SEEK_END)
// call before each write().
// f2.txt is less 2M bytes because of race condition since lseek and write is
// not atomic like just using O_APPEND

#include "utils.h"

int main(int argc, char **argv) {
    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s <filename> <num-bytes> <x>optional", argv[0]);
    }
    int out_fd;
    long i = 0;
    long num_bytes = getLong(argv[2], 1, "Bytes");
    int flags = O_CREAT | O_WRONLY | O_APPEND | O_EXCL;
    if (argc == 4 && strcmp(argv[3], "x") == 0) {
        flags &= ~O_APPEND;
        out_fd = open(argv[1], flags);
        if (out_fd == -1) {
            errExit("Open File");
        }
        while (i < num_bytes) {
            lseek(out_fd, 0, SEEK_END);
            write(out_fd, "a", 1);
            i++;
        }
        if (close(out_fd) == -1) {
            errExit("Close File");
        }
        exit(EXIT_SUCCESS);
    }
    out_fd = open(argv[1], flags);
    if (out_fd == -1) {
        errExit("Open Append File");
    }
    while (i < num_bytes) {
        write(out_fd, "a", 1);
        i++;
    }
    if (close(out_fd) == -1) {
        errExit("Close Append File");
    }
    exit(EXIT_SUCCESS);
}
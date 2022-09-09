#include "utils.h"

int main(int argc, char **argv) {
    char template[] =
        "/home/d1r3ct0r/programming/systems/MyWork/fileIO/txt/tempXXXXXX";
    int fd = mkstemp(template);
    if (fd == -1)
        errExit("mkstemp");
    printf("Generated filename was:%s\n\r", template);
    unlink(template);
    sleep(5);
    if (close(fd) == -1)
        errExit("close");
}
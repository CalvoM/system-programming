#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char **argv) {
#ifdef _XOPEN_SOURCE
    printf("_XOPEN_SOURCE is defined as %d\n\r", _XOPEN_SOURCE);
#endif
#ifdef _POSIX_SOURCE
    printf("_POSIX_SOURCE is defined\n\r");
#endif
#ifdef _BSD_SOURCE
    printf("_BSD_SOURCE is defined\n\r");
#endif
}
#include <gnu/libc-version.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Glibc version: %s\r\n", gnu_get_libc_version());
    return 0;
}

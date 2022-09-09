#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fd = fopen("./test.txt", "r");
    strerror();
    perror("File open");
}
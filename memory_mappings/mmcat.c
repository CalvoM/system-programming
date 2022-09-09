#include "utils.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        errExit("Open");
    struct stat sb;
    if (fstat(fd, &sb) == -1)
        errExit("fstat");
    char *addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");
    for (unsigned int i = 0; i < sb.st_size; i++) {
        write(1, addr + i, 1);
    }
    if (munmap(addr, sb.st_size) == -1)
        errExit("Unmap");
    exit(EXIT_SUCCESS);
}
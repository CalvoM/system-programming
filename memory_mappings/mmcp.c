#include "utils.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <source_file> <dest_file>\n", argv[0]);
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1)
        errExit("opening source");
    struct stat sb;
    if (fstat(src_fd, &sb) == -1)
        errExit("fstat");
    char *src_addr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, src_fd, 0);
    if (src_addr == MAP_FAILED)
        errExit("src mmap");
    if (close(src_fd) == -1)
        errExit("src file close");
    mode_t inPerms =
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // rw-rw-rw
    int dest_fd = open(argv[2], O_CREAT | O_RDWR, inPerms);
    if (dest_fd == -1)
        errExit("opening dest");
    if (ftruncate(dest_fd, sb.st_size) == -1)
        errExit("ftruncate");
    char *dest_addr =
        mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, dest_fd, 0);
    if (dest_addr == MAP_FAILED)
        errExit("dest mmap");
    if (close(dest_fd) == -1)
        errExit("dest file close");
    memcpy(dest_addr, src_addr, sb.st_size);
    exit(EXIT_SUCCESS);
}
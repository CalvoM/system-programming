#include "utils.h"
int main(int argc, char **argv) {
    int input_fd =
        open(argv[1], O_CREAT | O_WRONLY | O_APPEND, S_IWUSR | S_IRUSR);
    int input_fd2 = open(argv[1], O_WRONLY);
    if (input_fd == -1) {
        errExit("Open");
    }
    int dup_fd = dup(input_fd);
    if (dup_fd == -1) {
        errExit("Open Dup");
    }
    write(input_fd2, "------ ", 6);
    write(input_fd, "hello ", 6);
    write(dup_fd, "World", 5);
    close(input_fd);
    close(dup_fd);
}
#include "utils.h"

int main(int argc, char **argv) {
    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        errMsg("Error opening input file");
    }
    int output_fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (output_fd == -1) {
        errMsg("Error opening output file");
    }
    dup2(input_fd, STDIN_FILENO);
    dup2(output_fd, STDOUT_FILENO);
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d + %d = %d\n\r ", a, b, a + b);
    close(input_fd);
    exit(EXIT_SUCCESS);
}
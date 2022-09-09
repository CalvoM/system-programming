/**
 * Implements the TEE command using system calls
 * Add functionality for -a argument
 */
#include "utils.h"
int main(int argc, char **argv) {
    const int read_buf_size = 1024;
    char read_buf[read_buf_size];
    int input_fd = STDIN_FILENO;
    int output_fd;
    int outputFlags = O_CREAT | O_WRONLY;
    mode_t outputPerms =
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int opt;
    // check for any -argument provided
    while ((opt = getopt(argc, argv, "a")) != -1) {
        if (opt == '?') {
            // if unneeded argument provided
            usageErr("Only supported argument is -a\n\r");
        }
    }
    if (optind == 1) {
        // if -a is not provided
        outputFlags |= O_TRUNC;
    }
    int i = optind;
    while (i < argc) {
        // Write to all files provided
        output_fd = open(argv[i], outputFlags, outputPerms);
        if (output_fd == -1) {
            errExit("Error opening file: %s", argv[i]);
        }
        ssize_t read_bytes;
        while ((read_bytes = read(input_fd, read_buf, read_buf_size)) != 0) {
            if (write(output_fd, read_buf, read_bytes) != read_bytes)
                fatal("Error while writing to file");
        }
        // Stdin once read is empty so we copy to files then use them as the
        // input to other files.
        if (close(output_fd) == -1 || close(input_fd) == -1)
            errExit("Error closing file");
        input_fd = open(
            argv[i],
            O_RDONLY); // open the recent file copied to as the input to next
        i++;
    }
    // Stdout should be last after no error while writing output files
    ssize_t read_bytes;
    while ((read_bytes = read(input_fd, read_buf, read_buf_size)) != 0) {
        if (write(STDOUT_FILENO, read_buf, read_bytes) != read_bytes)
            fatal("Error while writing to file");
    }
    if (close(input_fd) == -1)
        errExit("Error closing file");
    exit(EXIT_SUCCESS);
}
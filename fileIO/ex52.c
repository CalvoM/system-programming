// Write a program that opens an existing file for writing with the O_APPEND
// flag, and then seeks to the beginning of the file before writing some data.
// Where does the data appear in the file? Why?
// ANS -> word written at the end of the file, when opened in APPEND mode, data
// is appended at end i.e. SEEK_SET will always be the end of the file
#include "utils.h"

int main(int argc, char **argv) {
    int fd =
        open("/home/d1r3ct0r/programming/systems/MyWork/fileIO/txt/numbers.txt",
             O_WRONLY | O_APPEND);
    if (fd == -1) {
        errExit("Open file");
    }
    lseek(fd, 0, SEEK_SET);
    char words[] = "Hello There";
    int num_written = write(fd, words, 11);
    printf("Content written: %d", num_written);
    if (close(fd)) {
        errExit("Closing");
    }
}
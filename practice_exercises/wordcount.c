/*  wordcount: Write a C program called wordcount that counts the words in the
   standard input. A word is a sequence of one or more characters delimited by
   white space. (Hint: there is a standard function to check whether a character
   is "white space".) The output should be the same as the command: % wc -w */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    size_t max_input_size = 512;
    char *input = (char *)malloc(max_input_size);
    int input_size = getline(&input, &max_input_size, stdin);
    int word_counter = 0;
    int word_size = 0;
    int i = 0;
    while (i < input_size) {
        if (isspace(input[i]) != 0 && word_size > 0) {
            word_counter++;
            word_size = 0;
        } else
            word_size++;
        i++;
    }
    printf("Word counter: %d\n", word_counter);
    free(input);
    return 0;
}

#include "practice.h"
#include <stdio.h>
#include <string.h>

/*
twotimes: Implement a function called twotimes that takes a string and returns
true if the given string consists of the concatenation of two identical
substrings. Test this function by writing a program that reads a string of up to
1000 characters from the standard input, and outputs YES or NO according to the
result of the twotimes function applied to the input string.

For example, the output of twotimes should be true when called with a parameter
mammamiamammamia and false when called with a parameter abracadabra.
*/
int twotimes(char *str) {
    int str_size = strlen(str);
    if (str_size % 2 != 0)
        return 0;
    int offset = str_size / 2;
    int i = 0;
    while (i < offset) {
        if (str[i] != str[i + offset])
            return 0;
        i++;
    }
    return 1;
}
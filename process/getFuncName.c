#include "utils.h"

int main(){
    printf("%s\n\r",program_invocation_name);
    printf("%s\n\r",program_invocation_short_name);
    exit(EXIT_SUCCESS);
}
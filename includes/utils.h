#ifndef UTILS_H_
#define UTILS_H_

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "error_functions.h"
#include "get_num.h"
typedef enum{
    FALSE,
    TRUE
}Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))
#endif
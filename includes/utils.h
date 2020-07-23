#ifndef UTILS_H_
#define UTILS_H_

#define _LARGEFILE64_SOURCE
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
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
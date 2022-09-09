#include "error_functions.h"
#include "ename.c.inc"
#include "utils.h"
#include <stdarg.h>

#ifdef __GNUC__
__attribute__((__noreturn__))
#endif

static void
terminate(Boolean useExit3) {
    char *s;
    // Check if dumpcore envvar is defined and is not an empty string; or check
    // `useExit3` variable
    s = getenv("EF_DUMPCORE");
    if (s != NULL && *s != '\0')
        abort();
    else if (useExit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

static void outputError(Boolean useErr, int err, Boolean flushStdout,
                        const char *format, va_list ap) {
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];
    vsnprintf(userMsg, BUF_SIZE, format, ap);
    if (useErr)
        snprintf(errText, BUF_SIZE, "[%s %s]",
                 (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?",
                 strerror(err));
    else
        snprintf(errText, BUF_SIZE, ":");
    snprintf(buf, BUF_SIZE, "ERROR %s %s\n\r", errText, userMsg);
    if (flushStdout)
        fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
}

/**
 * @brief prints message to stderr '\n' appended to end to output
 *        prints `errno` as returned by strerror
 */
void errMsg(const char *format, ...) {
    va_list argList;
    int savedErrno;
    savedErrno = errno;
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);
    errno = savedErrno;
}

/**
 * @brief Like `errMsg` and terminates the program by calling exit() or abort()
 */
void errExit(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);
    terminate(TRUE);
}

/**
 * @brief similar to errExit() but:
 *          1. does not flush stdout before printing
 *          2. calls _exit() instead of exit() - terminate without flush stdio
 * or invoking exit handlers Useful for library fxn that creates child process
 * and needs to terminate because of an error
 */
void err_exit(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errno, FALSE, format, argList);
    va_end(argList);
    terminate(FALSE);
}

/**
 * @brief same as errExit() but prints the error text corresponnding to value of
 * errno Used with POSIX threads API
 */
void errExitEN(int errnum, const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errnum, TRUE, format, argList);
    va_end(argList);
}

/**
 * @brief  Diagnose general errors including errors from library functions that
 * don't set errno Appends '\n' to
 */
void fatal(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    outputError(FALSE, 0, TRUE, format, argList);
    va_end(argList);
}

/**
 * @brief Diagnose errors in cmd-line argument usage
 */
void usageErr(const char *format, ...) {
    va_list argList;
    fflush(stdout);
    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    fflush(stderr);
    exit(EXIT_FAILURE);
}

/**
 * @brief Diagnose errors in the cmd-line specified to a program
 */
void cmdLineErr(const char *format, ...) {
    va_list argList;
    fflush(stdout);
    fprintf(stderr, "Command-line usage error: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    fflush(stderr);
    exit(EXIT_FAILURE);
}
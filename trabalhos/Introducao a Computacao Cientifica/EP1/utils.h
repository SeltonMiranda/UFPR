#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>


typedef double real_t;
typedef double rtime_t;
typedef char * string_t;

#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

#define PANIC(msg) do { \
    fprintf(stderr, COLOR_RED "[PANIC] %s:%d: %s\n" COLOR_RESET, __FILE__, __LINE__, msg); \
    exit(EXIT_FAILURE); \
} while(0)


double timestamp(void);

#endif // __UTILS_H__


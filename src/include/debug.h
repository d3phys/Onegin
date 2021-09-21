#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <stdio.h>
#include <cstdlib>
#include <ctype.h>

#define DEBUG

#ifdef DEBUG 
FILE *const DLOG = stderr;

#define $MSG(format, ...) {                                                                \
    fprintf(DLOG, "[%s %s, %d]: " format "\n", __TIME__, __FILE__, __LINE__, __VA_ARGS__); \
    fflush(DLOG);                                                                          \
}

#define $V(format, variable) {                                                                        \
    fprintf(DLOG, "[%s %s, %d]: " #variable "=" format "\n", __TIME__, __FILE__, __LINE__, variable); \
    fflush(DLOG);                                                                                       \
}

#define $LBL(format) {                                                        \
    fprintf(DLOG, "[%s %s, %d]: " format "\n", __TIME__, __FILE__, __LINE__); \
    fflush(DLOG);                                                             \
}

#define $$ {                                                                    \
    fprintf(DLOG, "[%s %s, %d]: I'm here" "\n", __TIME__, __FILE__, __LINE__); \
    fflush(DLOG);                                                              \
}

#else
#define $MSG(format, ...)
#define $VAL(format, variable)
#define $LBL(format)                                                                
#endif


#endif // _DEBUG_H_

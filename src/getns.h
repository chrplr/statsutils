#ifndef _GETNS_H
#define _GETNS_H
#define _POSIX_C_SOURCE 200809L

#include <time.h>

long int getns()
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    return spec.tv_nsec;
}
#endif

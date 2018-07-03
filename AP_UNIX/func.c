#include <errno.h>
#include <limits.h>
#include "ourhdr.h"

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define PATH_MAX_GUESS 1024

#ifdef OPEN_MAX
static int openmax = OPEN_MAX;
#else
static int openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

char * path_alloc(int *size)
{
    char    *ptr;

    if (pathmax == 0) {
        errno = 0;
        if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
            if (errno == 0)
                pathmax = PATH_MAX_GUESS;
            else
                err_sys("pathconf err for _PC_PATH_MAX");
        }
        else 
            pathmax++;
    }
    if ((ptr = malloc(pathmax + 1)) == NULL)
        err_sys("malloc error for pathname");

    if (size != NULL)
        *size = pathmax + 1;
    return (ptr);
}

int open_max(void)
{
    if (openmax == 0) {
        errno = 0;
        if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
            if (errno == 0)
                openmax = OPEN_MAX_GUESS;
            else
                err_sys("sysconf error for _SC_OPEN_MAX");
        }
    }
    return (openmax);
}


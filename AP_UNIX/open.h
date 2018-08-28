#include    <sys/types.h>
#include    <errno.h>
#include    "ourhdr.h"

#define     CL_OPEN     "open"      /* client's request for server */
#define     CS_OPEN     "/home/philip/open" /* server's well-know name */


                /* our function prototypes */
int    csopen(char *, int);


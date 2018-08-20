#include    <sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include    "ourhdr.h"

int
daemon_init(void)
{
    pid_t   pid;

    if ((pid = fork()) < 0)
        return (-1);
    else if (pid != 0)
        exit(0);   /* parent goes bye-bye */

    /* child continues */
    setsid();     /* become session leader */
    
    if (chdir("/") != 0)   /* change working directory */
        return (-1);

    umask(0);     /* clear our file mode creation mask */

    return (0);
}


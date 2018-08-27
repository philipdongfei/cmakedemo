#include    <sys/types.h>
#include    <sys/stat.h>
#include    <stropts.h>
#include    "ourhdr.h"


#define     FIFO_MODE   (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
            /* user rw, group rw, others rw */
int             /* returns fd if all ok, <0 on error */
serv_listen(const char *name)
{
    int     tempfd, fd[2], len;

                /* create a file: mount point for fattach() */
    unlink(name);
    if ((tempfd = create(name, FIFO_MODE)) < 0)
        return (-1);
    if (close(tempfd) < 0)
        return (-2);

    if (pipe(fd) < 0)
        return (-3);
       
                /* push connld & fattach() on fd[1] */
    if (ioctl(fd[1], I_PUSH, "connld") < 0)
        return (-4);
    if (fattach(fd[1], name) < 0)
        return (-5);

    return (fd[0]);     /* fd[0] is where client connections arrive */
}


/* Wait for a client connection to arrive, and accept it .
 * We also obtain the client's user ID.
 */

int         /* returns new fd if all OK, -1 on error */
serv_accept(int listenfd, uid_t *uidptr)
{
    struct strrecvfd    recvfd;

    if (ioctl(listenfd, I_RECVFD, &recvfd) < 0)
        return (-1);     /* could be EINTR if signal caught */

    if (uidptr != NULL)
        *uidptr = recvfd.uid;   /* effective uid of caller */
    return (recvfd.fd);    /* return the new descriptor */
}

/* Create a client endpoint and connect to a server.  */

int         /* returns fd if all OK, < 0 on error */
cli_conn(const char *name)
{
    int     fd;

            /* open the mounted stream */
    if ((fd = open(name, O_RDWR)) < 0)
        return (-1);

    if (isastream(fd) == 0)
        return (-2);

    return (fd);
}


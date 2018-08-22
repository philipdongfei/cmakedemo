#include    <sys/types.h>
#include    <sys/socket.h>
#include    "ourhdr.h"


/* SVR4 s_pipe(int) */
//int
//s_pipe(int fd[2])   /* two file descriptors return in fd[0] & fd[1] */
//{
//    return (pipe(fd));
//}


/* BSB s_pipe(int) */

int
s_pipe(int fd[2])    /* two file descriptors returned in fd[0] & fd[1] */
{
    return (socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}


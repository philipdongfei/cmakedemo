#include    <sys/types.h>
#include    <sys/socket.h>  /* struct msghdr */
#include    <sys/uio.h>     /* struct iovec */
#include    <errno.h>
#include    <stddef.h>
#include    "ourhdr.h"

/* Pass a file descriptor to another process.
 * If fd < 0, then -fd is sent back instead as the error status. 
 */

int 
send_fd(int clifd, int fd)
{
    struct iovec    iov[1];
    struct msghdr   msg;
    char            buf[2]; /* send_fd()/recv_fd() 2-byte protocol */

    iov[0].iov_base = buf;
    iov[0].iov_len = 2;

    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    if (fd < 0) {
        msg.msg_accrights = NULL;
        msg.msg_accrightlen = 0;
        buf[1] = -fd;    /* nonzero status means error */
        if (buf[1] == 0)
            buf[1] = 1; /* -256, etc. would screw up protocol */
    } else {
        msg.msg_accrights = (caddr_t)&fd;   /* addr of descriptor */
        msg.msg_accrightslen = sizeof(int);   /* pass 1 descriptor */
        buf[1] = 0;   /* zero status means OK */
    }
    buf[0] = 0;   /* null byte flag to recv_fd()  */

    if (sendmsg(clifd, &msg, 0) != 2)
        return(-1);
}


/* Receive a file descriptor from another process (a server).
 * In addition, any data received from the server is passed
 * to (*userfunc) (STDERR_FILENO, buf, nbytes). We have a
 * 2-byte protocol for receiving the fd from send_fd(). 
 */

int
recv_fd(int servfd, ssize_t (*userfunc)(int, const void *, size_t))
{
    int     newfd, nread, status;
    char    *ptr, buf[MAXLINE];
    struct iovec    iov[1];
    struct msghdr   msg;

    status = -1;
    for ( ; ; ) {
        iov[0].iov_base = buf;
        iov[0].iov_len = sizeof(buf);
        msg.msg_iov = iov;
        msg.msg_iovlen = 1;
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        msg.msg_accrights = (caddr_t)&newfd;  /* addr of descriptor */
        msg.msg_accrightslen = sizeof(int);  /* receive 1 descriptor */

        if ((nread = recvmsg(servfd, &msg, 0)) < 0)
            err_sys("recvmsg error");
        else if (nread == 0) {
            err_ret("connection closed by server");
            return (-1);
        }

                /* See if this is the final data with null & status.
                 * NULL must be next to last byte of buffer, status
                 * byte is last byte. Zero status means there must
                 * be a file descriptor to receive.
                 */
        for (ptr = buf; ptr < &buf[nread]; ) {
            if (*ptr++ == 0) {
                if (ptr != &buf[nread-1])
                    err_dump("message format error");
                status = *ptr & 255;
                if (status == 0) {
                    if (msg.msg_accrightslen != sizeof(int))
                        err_dump("status = 0 but no fd");
                    /* newfd = the new descriptor */
                } else
                    newfd = -status;
                nread -= 2;
            }
        }
        if (nread > 0)
            if ((*userfunc)(STDERR_FILENO, buf, nread) != nread)
                return (-1);
        if (status >= 0)    /* final data has arrived */
            return(newfd);  /* descriptor, or -status */
    }
}



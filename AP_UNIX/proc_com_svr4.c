#include    <sys/types.h>
#include    <stropts.h>
#include    "ourhdr.h"

/* Used when we had planned to send an fd using send_fd(),
 * but encountered an error instead. We send the error back
 * using the send_fd()/recv_fd() protocol 
 */

int
send_err(int clifd, int errcode, const char *msg)
{
    int     n;

    if ((n == strlen(msg)) > 0)
        if (writen(clifd, msg, n) != n)  /* send the error message */
            return (-1);
    
    if (errcode >= 0)
        errcode = -1;   /* must be negative */

    if (send_fd(clifd, errcode) < 0)
        return (-1);

    return (0);
}

/* Pass a file descriptor to another process.
 * If fd<0, then -fd is sent back instead as the error status .
 */

int
send_fd(int clifd, int fd)
{
    char    buf[2];    /* send_fd()/recv_fd() 2-byte protocol */
    buf[0] = 0;        /* null byte flag to recv_fd() */

    if (fd < 0) {
        buf[1] = -fd;    /* nonzero status means error */
        if (buf[1] == 0)
            buf[1] = 1;   /* -256, etc. would screw up protocol */
    } else {
        buf[1] = 0;     /* zero status means ok */
    }

    if (write(clifd, buf, 2) != 2)
        return (-1);
    if (fd >= 0)
        if (ioctl(clifd, I_SENDFD, fd) < 0)
            return(-1);
    return (0);
}

/* Receive a file descriptor from another process (a server).
 * In addition, any data received from the server is passed
 * to (*userfunc)(STDERR_FILENO, buf, nbytes). We have a
 * 2-byte protocol for receiving the fd from send_fd(). 
 */

int
recv_fd(int servfd, ssize_t (*userfunc)(int, const void *, size_t))
{
    int     newfd, nread, flag, status;
    char    *ptr, buf[MAXLINE];
    struct strbuf   dat;
    struct  strrecvfd   recvfd;

    status = -1;
    for ( ; ; ) {
        dat.buf = buf;
        dat.maxlen = MAXLINE;
        flag = 0;
        if (getmsg(servfd, NULL, &dat, &flag) < 0)
            err_sys("getmsg error");
        nread = dat.len;
        if (nread == 0) {
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
                if (ptr != &buf[nread - 1])
                    err_dump("message format error");
                status = *ptr & 255;
                if (status == 0) {
                    if (ioctl(servfd, I_RECVFD, &recvfd) < 0)
                        return (-1);
                    newfd = recvfd.fd;   /* new descriptor */
                } else
                    newfd = -status;
                nread -= 2;
            }
        }
        if (nread > 0)
            if ((*userfunc)(STDERR_FILENO, buf, nread) != nread)
                return (-1);

        if (status >= 0)  /* final data has arrived */
            return(newfd);  /* descriptor or -status */
    }
}


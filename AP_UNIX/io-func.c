#include    "ourhdr.h"

ssize_t                  /* Write "n" bytes to a descriptor */
writen(int fd, const void *vptr, size_t n)
{
    size_t      nleft;
    ssize_t     nwritten;
    const char  *ptr;

    ptr = vptr;   /* can't do pointer arithmetic on void* */
    nleft = n;
    while (nleft > 0) {
        if ((nwritten = write(fd, ptr, nleft)) <= 0)
            return (nwritten);   /* error */

        nleft -= nwritten;
        ptr   += nwritten;
    }
    return (n);
}

ssize_t             /* Read "n" bytes from a descriptor */
readn(int fd, void *vptr, size_t n)
{
    size_t   nleft;
    ssize_t  nread;
    char    *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0)
            return (nread);    /* error, return < 0 */
        else if (nread == 0)
            break;              /* EOF */

        nleft -= nread;
        ptr   += nread;
    }
    return (n - nleft);    /* return >= 0  */
}



#include    "opend.h"
#include    "ourhdr.h"
#include    <fcntl.h>

#define     MAXARGC     50   /* max number of arguments in buf */
#define     WHITE       " \t\n" /* white space for tokenizing arguments */


//void 
//request(char *buf, int nread, int fd)
//{
//    int     newfd;
//
//    if (buf[nread-1] != 0) {
//        sprintf(errmsg, "request not null terminated: %*.*s\n",
//                nread, nread,  buf);
//        send_err(fd, -1, errmsg);
//        return;
//    }
//
//                /* parse the arguments, set options */
//    if (buf_args(buf, cli_args) < 0) {
//        send_err(fd, -1, errmsg);
//        return;
//    }
//    if ((newfd = open(pathname, oflag)) < 0) {
//        sprintf(errmsg, "can't open %s: %s\n",
//                pathname, strerror(errno));
//        send_err(fd, -1, errmsg);
//        return;
//    }
//
//            /* send the descriptor */
//    if (send_fd(fd, newfd) < 0)
//        err_sys("send_fd error");
//    close(newfd);     /* we're done with descriptor */
//}
//

/* buf[] contains white-space separated arguments. We convert it
 * to an argv[] style array of pointers, and call the user's
 * function (*optfunc)() to process the argv[] array.
 * We return -1 to the caller if there's a problem parsing buf,
 * else we return whatever optfunc() returns. Note that user's
 * buf[] array is modified (nulls placed after each token).
 */

int
buf_args(char *buf, int (*optfunc)(int, char **))
{
    char    *ptr, *argv[MAXARGC];
    int     argc;

    if (strtok(buf, WHITE) == NULL)   /* an argv[0] is required */
        return(-1);
    argv[argc = 0] = buf;

    while ((ptr = strtok(NULL, WHITE)) != NULL) {
        if (++argc >= MAXARGC-1)   /* -1 for room for NULL at end */
            return (-1);
        argv[argc] = ptr;
    }
    argv[++argc] = NULL;

    return ((*optfunc)(argc, argv));
        /* Since argv[] pointers point into the user's buf[]
         * user's function can just copy the pointers, even
         * though argv[] array will disappear on return. 
         */
}

/* This function is called by buf_args(), which is called by
 * request(). buf_args() has broken up the client's buffer
 * into an argv[] style array, which we now process.
 */

//int
//cli_args(int argc, char **argv)
//{
//    if (argc != 3 || strcmp(argv[0], CL_OPEN) != 0 ) {
//
//        strcpy(errmsg, "usage: <pathname> <oflag>\n");
//        return (-1);
//    }
//
//    pathname = argv[1];   /* save ptr to pathname to open */
//    oflag = atoi(argv[2]);
//    return (0);
//}
//

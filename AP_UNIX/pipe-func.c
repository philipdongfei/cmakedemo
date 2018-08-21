#include    <sys/wait.h>
#include    <errno.h>
#include    <fcntl.h>
#include    "ourhdr.h"

static pid_t     *childpid = NULL;
                     /* ptr to array allocated at run-time */
static int      maxfd;   /* from our open_max(), Program 3.3 */

#define SHELL   "bin/sh"


static int  pfd1[2], pfd2[2];

void
TELL_WAIT(void)
{
    if (pipe(pfd1) < 0 || pipe(pfd2) < 0)
        err_sys("pipe error");
}

void
TELL_PARENT(pid_t pid)
{
    if (write(pfd2[1], "c", 1) != 1)
        err_sys("pipe error");
}

void
WAIT_PARENT(void)
{
    char    c;

    if (read(pfd1[0], &c, 1) != 1)
        err_sys("read error");
    if (c != 'p')
        err_quit("WAIT_PARENT: incorrect data");
}

void
TELL_CHILD(pid_t pid)
{
    if (write(pfd1[1], "p", 1) != 1)
        err_sys("write error");
}

void 
WAIT_CHILD(void)
{
    char    c;

    if (read(pfd2[0], &c, 1) != 1)
        err_sys("read error");
    if (c != 'c')
        err_quit("WAIT_CHILD: incorrent data");
}

FILE  *
popen(const char *cmdstring, const char *type)
{
    int     i, pfd[2];
    pid_t   pid;
    FILE    *fp;

             /* only allow "r" or "w" */
    if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0) {
        errno = EINVAL;        /* required by POSIX.2 */
        return (NULL);
    }

    if (childpid == NULL) {      /* first time throught */
             /* allocate zeroed out array for child pids */
        maxfd = open_max();
        if ((childpid = calloc(maxfd, sizeof(pid_t))) == NULL)
            return (NULL);
    }
    if (pipe(pfd) < 0)
        return(NULL);   /* errno set by pipe() */
    
    if ((pid = fork()) < 0)
        return(NULL);   /* errno set by fork() */
    else if (pid == 0) {         /* child */
        if (*type == 'r') {
            close(pfd[0]);
            if (pfd[1] != STDOUT_FILENO) {
                dup2(pfd[1], STDOUT_FILENO);
                close(pfd[1]);
            }
        } else {
            close(pfd[1]);
            if (pfd[0] != STDIN_FILENO) {
                dup2(pfd[0], STDIN_FILENO);
                close(pfd[0]);
            }
        }
            /* close all descriptors in childpid[] */
        for (i = 0; i < maxfd; i++)
            if (childpid[i] > 0)
                close(i);
        execl(SHELL, "sh", "-c", cmdstring, (char *)0);
        _exit(127);
    }
               /* parent */
    if (*type == 'r') {
        close(pfd[1]);
        if ((fp = fdopen(pfd[0], type)) == NULL)
            return(NULL);
    } else {
        close(pfd[0]);
        if ((fp = fdopen(pfd[1], type)) == NULL)
            return (NULL);
    }
    childpid[fileno(fp)] = pid;  /* remember child pid for this fd */
    return (fp);
}

int
pclose(FILE *fp)
{
    int     fd, stat;
    pid_t   pid;

    if (childpid == NULL)
        return (-1);     /* popen() has never been called */

    fd = fileno(fp);
    if ((pid = childpid[fd]) == 0)
        return (-1);       /* fp wasn't opened by popen() */

    childpid[fd] = 0;
    if (fclose(fp) == EOF)
        return (-1);

    while (waitpid(pid, &stat, 0) < 0)
        if (errno != EINTR)
            return(-1);     /* error other than EINTR from waitpid() */

    return(stat);      /* return child's termination status */
}




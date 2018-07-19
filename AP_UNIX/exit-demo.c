#include <sys/types.h>
#include <sys/wait.h>
#include "ourhdr.h"

int main(void)
{
    pid_t    pid;
    int      status;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(7);

    if (wait(&status) != pid) /* wait for child */
        err_sys("wait error");
    pr_exit(status); /* and print its status */

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) /* child */
        abort();

    if (wait(&status) != pid) /* wait for child */
        err_sys("wait error");
    pr_exit(status); /* print its status */

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) /* child */
        status /= 0;

    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);   /* and print its status */
    exit(0);
}


#include    <errno.h>
#include    <signal.h>
#include    "ourhdr.h"
#include    <sys/signal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>

void pr_mask(const char *str)
{
    sigset_t    sigset;
    int         errno_save;

    errno_save = errno;   /* we can be called by signal handlers */
    if (sigprocmask(0, NULL, &sigset) < 0)
        err_sys("sigprocmask error");

    printf("%s", str);
    if (sigismember(&sigset, SIGINT)) printf("SIGINT ");
    if (sigismember(&sigset, SIGQUIT)) printf("SIGQUIT ");
    if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
    if (sigismember(&sigset, SIGALRM)) printf("SIGALRM ");
        /* remaining signals can go here */
    printf("\n");
    errno = errno_save;
}

Sigfunc * 
signal(int signo, Sigfunc *func)
{
    struct sigaction    act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef  SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;   /* SunOS */
#endif
    } else {
#ifdef  SA_RESTART
        act.sa_flags |= SA_RESTART;    /* SVR4, 4.3+BSD */
#endif
    }
    if (sigaction(signo, &act, &oact) < 0)
        return (SIG_ERR);
    return (oact.sa_handler);
}

Sigfunc *
signal_intr(int signo, Sigfunc *func)
{
    struct sigaction  act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
#ifdef  SA_INTERRUPT   /* SunOS */
    act.sa_flags |= SA_INTERRUPT;
#endif
    if (sigaction(signo, &act, &oact) < 0)
        return (SIG_ERR);
    return (oact.sa_handler);
}

void
abort(void)    /* POSIX-style abort() function */
{
    sigset_t    mask;
    struct sigaction    action;

        /* caller can't ignore SIGABRT, if so reset to default */
    sigaction(SIGABRT, NULL, &action);
    if (action.sa_handler == SIG_IGN) {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }

    if (action.sa_handler == SIG_DFL)
        fflush(NULL);              /* flush all open stdio stream */

        /* caller can't block SIGABRT; make sure it's unblocked  */
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT); /* mask has only SIGABRT turned off */
    sigprocmask(SIG_SETMASK, &mask, NULL);

    kill(getpid(), SIGABRT);  /* send the signal */

        /* if we're here, process caught SIGABRT and returned */
    fflush(NULL);     /* flush all open stdio streams */

    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);   /* reset disposition to default */
    sigprocmask(SIG_SETMASK, &mask, NULL);  /* just in case ... */

    kill(getpid(), SIGABRT);   /* and one more time  */

    exit(1);   /* this should never be executed ... */
}



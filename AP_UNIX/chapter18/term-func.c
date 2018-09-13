#include    <stdio.h>
#include    <string.h>
#include    <termios.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <dirent.h>
#include    <limits.h>
#include    <unistd.h>
#include    <signal.h>

#define DEV     "/dev/"   /* device directory */
#define DEVLEN  sizeof(DEV)-1   /* sizeof includes null at end */

#define  MAX_PASS_LEN    8   /* max #chars for user to enter  */

static struct termios    save_termios;
static int               ttysavefd = -1;
static enum { RESET, RAW, CBREAK } ttystate = RESET;

static char ctermid_name[L_ctermid];

char *
ctermid(char *str)
{
    if (str == NULL)
        str = ctermid_name;
    return (strcpy(str, "/dev/tty"));       /* strcpy() returns str */
}

int 
isatty(int fd)
{
    struct termios  term;
    return (tcgetattr(fd, &term) != -1);  /* true if no error (is a tty)  */
}

char *
ttyname(int fd)
{
    struct stat    fdstat, devstat;
    DIR            *dp;
    struct dirent  *dirp;
    static char    pathname[_POSIX_PATH_MAX + 1];
    char           *rval;

    if (isatty(fd) == 0)
        return (NULL);
    if (fstat(fd, &fdstat) < 0)
        return (NULL);
    if (S_ISCHR(fdstat.st_mode) == 0)
        return (NULL);

    strcpy(pathname, DEV);
    if ((dp = opendir(DEV)) == NULL)
        return(NULL);
    rval = NULL;
    while ((dirp = readdir(dp)) !=  NULL) {
        if (dirp->d_ino != fdstat.st_ino)
            continue;    /* fast test to skip most entries */

        strncpy(pathname + DEVLEN, dirp->d_name, _POSIX_PATH_MAX - DEVLEN);
        if (stat(pathname, &devstat) < 0)
            continue;
        if (devstat.st_ino == fdstat.st_ino &&
                devstat.st_dev == fdstat.st_dev) {   /* found a match */
                    rval = pathname;
                    break;
        }
    }
    closedir(dp);
    return (rval);
}


char *
getpass(const char *prompt)
{
    static char    buf[MAX_PASS_LEN + 1];    /* null byte at end */
    char           *ptr;
    sigset_t       sig, sigsave;
    struct termios term, termsave;
    FILE           *fp;
    int            c;

    if ((fp = fopen(ctermid(NULL), "r+")) == NULL)
        return (NULL);
    setbuf(fp, NULL);

    sigemptyset(&sig);    /* block SIGINT & SIGTSTP, save signal mask */
    sigaddset(&sig, SIGINT);
    sigaddset(&sig, SIGTSTP);
    sigprocmask(SIG_BLOCK, &sig, &sigsave);

    tcgetattr(fileno(fp), &termsave);  /* save tty state */
    term = termsave;                   /* structure copy */
    term.c_lflag &= ~(ECHO | ECHOE | ECHONL);
    tcsetattr(fileno(fp), TCSAFLUSH, &term);

    fputs(prompt, fp);

    ptr = buf;
    while ((c = getc(fp)) != EOF && c != '\n') {
        if (ptr < &buf[MAX_PASS_LEN])
            *ptr++ = c;

    }
    *ptr = 0;      /* null terminate */
    putc('\n', fp);   /* we echo a newline */ 

                    /* restore tty state */
    tcsetattr(fileno(fp), TCSAFLUSH, &termsave);

                    /* restore signal mask */
    sigprocmask(SIG_SETMASK, &sigsave, NULL);
    fclose(fp);     /* done with /dev/tty */
    return (buf);
}

int
tty_cbreak(int fd)   /*  put terminal into a cbreak mode */
{
    struct termios  buf;
    
    if (tcgetattr(fd, &save_termios) < 0)
        return (-1);

    buf = save_termios;   /* structure copy */
    buf.c_lflag &= ~(ECHO | ICANON);
                     /* echo off, canonical mode off */
    buf.c_cc[VMIN] = 1; /* Case B: 1 byte at a time, no timer */
    buf.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
        return (-1);
    ttystate = CBREAK;
    ttysavefd = fd;
    return (0);
}

int 
tty_raw(int fd)   /* put terminal into a raw mode */
{
    struct termios  buf;
    if (tcgetattr(fd, &save_termios) < 0)
        return (-1);

    buf = save_termios;  /* structure copy */
    buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
                        /* ehco off, canonical mode off, extended input
                         * processing off, signal chars off */
    buf.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
                       /* no SIGINT on BREAK, CR-to-NL off, input parity
                        * check off, don't strip 8th bit on input,
                        * output flow control off */
    buf.c_cflag &= ~(CSIZE | PARENB);
                       /* clear size bits, parity checking off */
    buf.c_cflag |= CS8;
                       /* set 8 bits/char */
    buf.c_oflag &= ~(OPOST);
                      /* output processing off */
    buf.c_cc[VMIN] = 1; /* Case B: 1 byte at a time, no timer */
    buf.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
        return (-1);
    ttystate = RAW;
    ttysavefd = fd;
    return(0);
}

int tty_reset(int fd)    /* restore terminal's mode */
{
    if (ttystate != CBREAK && ttystate != RAW)
        return (0);
    if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
        return (-1);
    ttystate = RESET;
    return (0);
}

void 
tty_atexit(void)    /* can be set up by atexit(tty_atexit) */
{
    if (ttysavefd >= 0)
        tty_reset(ttysavefd);
}

struct termios *
tty_termios(void)   /* let caller see original tty state */
{
    return (&save_termios);
}


#include    <sys/types.h>
#include    <sys/socket.h>
#include    <sys/stat.h>
#include    <sys/un.h>
#include    <stddef.h>
#include    <time.h>
#include    "ourhdr.h"

/* Create a server endpoint of a connection. */

int     /* returns fd if all OK, <0 on error */
serv_listen(const char *name)
{
    int     fd, len;
    struct sockaddr_un  unix_addr;

            /* create a Unix domain stream socket */
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        return (-1);

    unlink(name);    /* in case it already exists */

                    /* fill in socket address structure */
    memset(&unix_addr, 0, sizeof(unix_addr));
    unix_addr.sun_family = AF_UNIX;
    strcpy(unix_addr.sun_path, name);
#ifdef  SCM_RIGHTS      /* 4.3BSD Reno and later */
    /*
     * len = sizeof(unix_addr.sun_len) + sizeof(unix_addr.sun_family) +
        strlen(unix_addr.sun_path) + 1;
    unix_addr.sun_len = len;
    */
    len = strlen(unix_addr.sun_path) + sizeof(unix_addr.sun_family);
#else
    len = strlen(unix_addr.sun_path) + sizeof(unix_addr.sun_family);
#endif

                /* bind the name to the Descriptor */
    if (bind(fd, (struct sockaddr *) &unix_addr, len) < 0)
        return (-2);

    if (listen(fd, 5) < 0)   /* tell kernel we're a server */
        return (-3);

    return (fd);
}

/* Create a client endpoint and connect to a server. */

#define CLI_PATH    "/var/tmp/"     /* +5 for pid = 14 chars */
#define CLI_PERM    S_IRWXU         /* rwx for user only */

int     /* returns fd if all OK, <0 on error */
cli_conn(const char *name)
{
    int     fd, len;
    struct sockaddr_un  unix_addr;

            /* create a Unix domain stream socket */
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        return (-1);

            /* fill socket address structure w/our address */
    memset(&unix_addr, 0, sizeof(unix_addr));
    unix_addr.sun_family = AF_UNIX;
    sprintf(unix_addr.sun_path, "%s%05d", CLI_PATH, getpid());
#ifdef  SCM_RIGHTS  /* 4.3BSD Reno and later */
    /*
     * len = sizeof(unix_addr.sun_len) + sizeof(unix_addr.sun_family) + 
        strlen(unix_addr.sun_path) + 1;
    unix_addr.sun_len = len;
    */
    len = strlen(unix_addr.sun_path) + sizeof(unix_addr.sun_family);
    if (len != 16)
        err_quit("length != 16");    /* hack */
#else       /* vanilla 4.3BSD */
    len = strlen(unix_addr.sun_path) + sizeof(unix_addr.sun_family);
    if (len != 16)
        err_quit("length != 16");    /* hack */
#endif

    unlink(unix_addr.sun_path);    /* in case it already exists */
    if (bind(fd, (struct sockaddr *)&unix_addr, len) < 0)
        return (-2);
    if (chmod(unix_addr.sun_path, CLI_PERM) < 0)
        return (-3);

                /* fill socket address structure w/server's addr */
    memset(&unix_addr, 0, sizeof(unix_addr));
    unix_addr.sun_family = AF_UNIX;
    strcpy(unix_addr.sun_path, name);
#ifdef  SCM_RIGHTS   /* 4.3BSD Reno and later */
    /*
     * len = sizeof(unix_addr.sun_len) + sizeof(unix_addr.sun_family) + 
        strlen(unix_addr.sun_path) + 1;
    unix_addr.sun_len = len;
    */
    len = strlen(unix_addr.sun_path) + sizeof(unix_addr.sun_family);
#else     /* vanilla 4.3BSD */
    len = strlen(unix_addr.sun_path) + sizeof(unix_addr.sun_family);
#endif

    if (connect(fd, (struct sockaddr *)&unix_addr, len) < 0)
        return (-4);

    return (fd);
}


#define STALE   30  /* client's name can't be older than this (sec) */

/* Wait for a client connection to arrive, and accept it.
 * We also obtain the client's user ID from the pathname
 * that it must bind before calling us. 
 */

int     /* returns new fd if all OK, <0 on error */
serv_accept(int listenfd, uid_t *uidptr)
{
    int     clifd, len;
    time_t  staletime;
    struct sockaddr_un  unix_addr;
    struct stat     statbuf;

    len = sizeof(unix_addr);
    if ((clifd = accept(listenfd, (struct sockaddr *) &unix_addr, &len)) < 0)
        return (-1);     /* often errno=EINTR, if signal caught */

                /* obtain the client's uid from its calling address */
#ifdef  SCM_RIGHTS    /* 4.3BSD Reno and later */
    //len -= sizeof(unix_addr.sun_len) - sizeof(unix_addr.sun_family);
    len -= sizeof(unix_addr.sun_family);   /* len of pathname */
#else       /* vanilla 4.3BSD */
    len -= sizeof(unix_addr.sun_family);   /* len of pathname */
#endif
    unix_addr.sun_path[len] = 0;     /* null terminate */

    if (stat(unix_addr.sun_path, &statbuf) < 0)
        return (-2);
#ifdef  S_ISSOCK     /* not defined for SVR4 */
    if (S_ISSOCK(statbuf.st_mode) == 0)
        return (-3);    /* not a socket */
#endif
    if ((statbuf.st_mode & (S_IRWXG | S_IRWXO)) || 
            (statbuf.st_mode & S_IRWXU) != S_IRWXU)
        return (-4);    /* is not rwx--------- */
    staletime = time(NULL) - STALE;
    if (statbuf.st_atime < staletime || 
            statbuf.st_ctime < staletime || 
            statbuf.st_mtime < staletime)
        return (-5);    /* i-node is too old */

    if (uidptr != NULL)
        *uidptr = statbuf.st_uid;   /* return uid of caller */

    unlink(unix_addr.sun_path); /* we're done with pathname now */

    return (clifd);
}




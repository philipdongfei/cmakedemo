#include    "opend-daemon.h"
#include    <syslog.h>

            /* define global variables */
int     debug;
char    errmsg[MAXLINE];
int     oflag;
char    *pathname;
Client  *client = NULL;
int     client_size;

int
main(int argc, char *argv[])
{
    int     c;

    log_open("open.serv", LOG_PID, LOG_USER);
    opterr = 0;     /* don't want getopt() writing to stderr */
    while((c = getopt(argc, argv, "d")) != EOF) {
        switch(c) {
            case 'd':   /* debug */
                debug = 1;
                break;
            case '?':
                err_quit("unrecognized option: -%c", optopt);
        }
    }
    if  (debug == 0)
        daemon_init();
    loop();    /* never returns */
}


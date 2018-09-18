#include    <sys/types.h>
#include    <termios.h>
#include    <sys/ioctl.h>
#include    "ourhdr.h"

pid_t   pty_fork(int *ptrfdm, char *slave_name,
        const struct termios *slave_termios,
        const struct winsize *slave_winsize);



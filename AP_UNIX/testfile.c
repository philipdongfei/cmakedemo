#include    <sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include    "ourhdr.h"

int 
main(int argc, char *argv[])
{
    int fdout;

    if (argc != 2)
        err_quit("usage error");

    if ((fdout = open(argv[1], O_RDWR | O_CREAT | O_TRUNC,
                    FILE_MODE)) < 0)
        err_sys("creat %s error", argv[1]);

    if (lseek(fdout, 256-1, SEEK_SET) == -1)
        err_sys("lseek error");
    if (write(fdout, "", 1) != 1)
        err_sys("write error");
    if (write(fdout, "end", 3) != 3)
        err_sys("write 3 error");

    close(fdout);
    exit(0);
}



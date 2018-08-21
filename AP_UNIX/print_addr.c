#include    <sys/types.h>
#include    <sys/ipc.h>
#include    <sys/shm.h>
#include    "ourhdr.h"

#define ARRAY_SIZE  40000
#define MALLOC_SIZE 100000
#define SHM_SIZE    100000
#define SHM_MODE    (SHM_R | SHM_W)  /* user read/write */

char    array[ARRAY_SIZE];     /* uninitialized data = bss */

int
main(void)
{
    int     shmid;
    char    *ptr, *shmptr;

    printf("array[] from 0x%x to 0x%x\n", &array[0], &array[ARRAY_SIZE]);
    printf("stack around 0x%x\n", &shmid);

    if ((ptr = malloc(MALLOC_SIZE)) == NULL)
        err_sys("malloc error");
    printf("malloced from 0x%x to 0x%x\n", ptr, ptr+MALLOC_SIZE);

    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
        err_sys("shmget error");
    if ((shmptr = shmat(shmid, 0, 0)) == (void *) -1)
        err_sys("shmat error");
    printf("shared memory attached from 0x%x to 0x%x\n",
            shmptr, shmptr+SHM_SIZE);
    if (shmctl(shmid, IPC_RMID, 0) < 0)
        err_sys("shmctl error");

    exit(0);
}


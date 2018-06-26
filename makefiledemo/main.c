#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("Hello World!\n");
    printf("test");
    int i, pid;
    for(i = 0; i<argc; i++)
        printf("%s\n",argv[i]);
    if (0 == (pid = fork())) {//child 
        printf("child process\n");
        exit(0);
    }
    printf("parent process\n");

    exit(0);
}


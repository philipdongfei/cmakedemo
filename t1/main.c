#include <stdio.h>
#include <stdlib.h>
#include "projectConfigure.h"

int main(void)
{
    printf("Hello World from t1 Main!\n");
    printf("%s\n",PROJECT_BINARY_DIR);
#ifdef DEBUG_BUILD
    int v = 10;
    printf("the value of v is %d\n", v);
#endif
    int i = 0, t=0;
    for(; i<100; i++)
        t += i;
    printf("t=%d\n", t);
    printf("All ok\n");
    char *pBuf = (char*)malloc(1024);
    memset(pBuf,0x0,1024);
    sprintf(pBuf,"test a cdash\n");
    printf("%s", pBuf);
    free(pBuf);

    return 0;
}


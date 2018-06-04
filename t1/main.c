#include <stdio.h>
#include "projectConfigure.h"

int main(void)
{
    printf("Hello World from t1 Main!\n");
    printf("%s\n",PROJECT_BINARY_DIR);
#ifdef DEBUG_BUILD
    int v = 10;
    printf("the value of v is %d\n", v);
#endif
    return 0;
}


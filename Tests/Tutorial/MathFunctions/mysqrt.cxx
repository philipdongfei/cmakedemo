#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mysqrt(double inValue)
{
    if (inValue <= 0)
        return 0;
    double result = 0.0;
    // if we have both log and exp then use them
#if defined (HAVE_LOG) && defined (HAVE_EXP)
    printf("have log&exp\n");
    result = exp(log(inValue)*0.5);
#else
    printf("have not log&exp\n");
    for(int i = 1; i<=inValue/2; i++)
    {
        if (inValue == i*i)
        {
            result = i;
        }
    }
#endif
    return result;
}

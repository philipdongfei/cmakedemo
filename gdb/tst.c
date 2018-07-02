#include <stdio.h>
#include <stdlib.h>

int func(int n)
{
    int sum=0, i;
    int *array = (int*)malloc(n * sizeof(int));
    for (i=0; i<n; i++)
    {
        array[i] = i;
        sum += i;
    }
    free(array);

    return sum;
}

int main()
{
    int i; 
    long result = 0;
    for (i=1; i<=100; i++)
        result += i;

    printf("result[1-100] = %i \n", (int)result);
    printf("result[1-250] = %d \n", func(250));
}


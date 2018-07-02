#include <stdio.h>

/*char ascii_hello[] = {72, 101, 108,
    111, 44, 32, 119, 111, 114, 108, 
    100, 33, 10, 0};
char ibm1047_hello[] = {
    200, 133, 147, 147, 150, 107, 64, 
    166, 150, 153, 147, 132, 90, 37,
    0};
    */
void 
hello()
{
    static char hello[] = "hello-hello";
    static struct { char c; short s; int i;}
    __attribute__((packed)) mixed
    = { 'c', 0x1234, 0x87654321 };
    printf ("%s\n", hello);
}


void main()
{
    printf("Hello, world!\n");
}



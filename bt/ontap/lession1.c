#include <stdio.h>

union {

    char v1;
    int v2;
    long long f3;

} u9;



void main()
{
    union u9;
    u9.v2 = 0x12345648; 

    printf ("%c \n", u9.v1);
    printf ("%x \n", u9.v2);
    printf ("%x \n", u9.f3);
}
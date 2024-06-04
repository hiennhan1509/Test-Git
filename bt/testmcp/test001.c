#include <stdio.h>

void main()
{

    unsigned int a = 0;
    unsigned short b = 1;
    unsigned short c = 5;
    a = ((b<<8)|c);
    printf("%x",a);

}
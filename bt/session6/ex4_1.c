#include <stdio.h>

short n1[4] = {20023,2,3,4};
float f2[4] = {1.2, 2.3, 3.4, 4.5};
char s3[5] = "abcd";


void *p[3] = {n1, f2, s3};

void main()
{
    for (int i = 0; i < 8; i+=2)
    {
        printf("%d \n", (*(short*)(p[0]+i)));
    }

    for (int i = 0; i < 16; i+=4)
    {
        printf("%f \n", (*(float*)(p[1]+i)));
    }

    printf("%s \n", p[2]);

}
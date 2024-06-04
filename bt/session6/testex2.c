#include <stdio.h>
#include <stdlib.h>

void main()
{
    short* p;
    p = (short*)malloc(sizeof(short)*32);
    short arr[4][8];
    int i = 0;
    int j = 0;
    int n = 32;
    for ( i = 0; i < 32; i++)
    {
        p[i] = i+10;
        printf("p = %d\n",p[i]);
    }
    

    for (i = 0; i < n; i++)
    {
        arr[i/8][i%8] = p[i];
        printf("%d //", arr[i/8][i%8]);
    }
    

}
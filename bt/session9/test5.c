#include <stdio.h>


void main()
{
    int x = 3;
    int *p = &x;
    int y = x / *p; /* p point to x */
    printf("%d ", y);
}
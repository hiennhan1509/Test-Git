#include <stdio.h>

void swap1(int a, int b)
{
    int c;
    c = a;
    a = b;
    b = c;
    printf ("%d %d", a, b);
}

void main()
{
    int x = 23;
    int y = 11;

    swap1(x, y);
}
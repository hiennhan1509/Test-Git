#include <stdio.h>

int a = 11;
int b = 23;
int c;

void swap(int *x, int *y);

void main()
{
    swap(&a, &b);
    printf("%d %d", a, b);
}

void swap(int *x, int *y)
{
    c = *x;
    *x = *y;
    *y = c;
}
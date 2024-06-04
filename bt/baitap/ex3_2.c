#include <stdio.h>

int arr[10] = {0, 1};
int i = 2;

void fib();

void main()
{
    printf("%d %d ", arr[0], arr[1]);
    fib();
}

void fib()
{       
    if (i < 10)
    {
    arr[i] = arr[i-1] + arr [i-2];
    printf("%d ",arr[i]);
    i++;
    fib();
    }
}
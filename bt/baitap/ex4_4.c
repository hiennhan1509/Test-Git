#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char *arr, int n);


void main()
{
    
    char str[100] = "abcd efzxgh 1234";
    int nsize = strlen(str);
    reverse(str, nsize);
    printf("%s", str);
}

void reverse(char *arr, int n)
{
    char *temp;
    for (int i = 0; i < n/2; i++)
    {
        *temp = arr[i];
        arr[i] = arr[n-i-1];
        arr[n-i-1] = *temp;
    }
    
}

void swap(int x, int y, char a[x], char b[y])
{
    char *temp;
    *temp = a[x];
    a[x] = b[y];
    b[y] = *temp;
}
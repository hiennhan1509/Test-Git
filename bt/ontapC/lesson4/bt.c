#include "stdio.h"

unsigned char arr[] = "abcd efgh 1234";

void main()
{
    unsigned short n = sizeof(arr);
    unsigned char temp;
    for (int i = 0; i < n/2; i++)
    {
        temp = arr[i];
        arr[i] = arr[n-i-2];
        arr[n-i-2] = temp;
    }
    printf("%s",arr);
}
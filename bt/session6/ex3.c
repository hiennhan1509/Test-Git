#include <stdio.h>
#include <stdlib.h>

void SwapAddr(int *p1 , int *p2)
{

    
    printf("orginal address 0x%X 0x%X", &p1, &p2);
    
    int *temp = p1;
    p1 = p2;
    p2 = temp;

    printf(" \nswap address 0x%X 0x%X", &p1, &p2);
}



void main()
{
    int* p1 = (int*)malloc(sizeof(int) * 10);
    int* p2 = (int*)malloc(sizeof(int) * 20);



    SwapAddr(p1,p2);
    free(p1);
    free(p2);
}
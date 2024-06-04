#include <stdio.h>

float arr[5][7] = {{1,2,3,4,5,6,7}, {5,5,5,5,5,5,5}};

float *p1 = arr[0];
int i;
int j;

void main()
{
    for(i = 0; i < 3 ; i ++)
    {
        for ( j = 0; j < 7; j++)
        {
            *p1 = p1[i*7+j];
            printf("%.2f \\", *p1);
            
        }
        
    }
}

#include <stdio.h>
#include <stdlib.h>

short arr[4][8] = {{1,2,3,4,5,6,7,8}, {5,5,5,5,5,5,5}};

int i = 0;
int j = 0;
void main()
{   
    short* p1 = (short*) malloc(sizeof(short)*32);
    

    for (i = 0; i < 4; i++)
    {
        for ( j = 0; j < 8; j++)
        {
            p1[i*8+j] = arr[i][j];
            printf("%d \\", p1[i*8+j] );
        }

    }
    

    free(p1);
}
#include <stdio.h>
#include <stdlib.h>

int *g_cP;
int i;


void main()
{   

    int *g_cP = (int*) malloc (sizeof(int)*5);

    for ( i = 0; i < 5; i++)
    {
        scanf("%d", &g_cP[i]);
    }
    
        printf("%d\n", g_cP[3]);

}    
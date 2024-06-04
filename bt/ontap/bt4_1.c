#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 0;
void main()
{
    int *p = (int*) malloc (sizeof(int)*10);
    
    memset(p,0,sizeof(int)*10);
    p[3] = 2222;
    p[6] = 10;
    printf("%d \n", p[6]);
    for(i = 0; i <10; i++)
    {
        printf("%d ",p[i]);
    }

    printf("\n");    
    memcpy(p+7,p+3,3);
    
    for(i = 0; i <10; i++)
    {
        printf("%d ",p[i]);
    }

    free(p);
}

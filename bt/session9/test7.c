#include <stdio.h>
#include <string.h>

char *p;

void main()
{
    // if(p == (char *) 0)
    //     printf("1\n");

    if(strcmp(p, (char *) 0) == 0)
        printf("1");

}
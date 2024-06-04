#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    char *curstr;
    char *prvstr;
    curstr = (char *)malloc(10);
    prvstr = (char *)malloc(10);
    //*prvstr = *curstr;
    prvstr = curstr;

    strcpy(curstr, "abc");
    printf("%s\n", prvstr);

    strcpy(curstr+3, "xyz");
    printf("%s", prvstr);

    free(curstr);
    free(prvstr);

}
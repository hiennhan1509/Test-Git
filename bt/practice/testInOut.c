#include <stdio.h>
#include <string.h>

void main()
{
    char s[64];
    unsigned int i = 0;
    FILE *fp = NULL;
    fp = fopen("test.txt", "rb");
    if (fp == NULL)
        return;
    memset(s, 0, 64);
    // for (i = 0; i < 3; i++)
    // {
    //     fgets(s, 64, fp);
    //     printf("\n[%d]: |%s|", i, s);
    // }
    // while (feof(fp) == 0)
    // {
    //     fgets(s, 64, fp);
    //     printf("\n[%d]: |%s|", i, s);
    //     i++;
    // }


    fread(s, 1, 64, fp);
    printf("|%s|", s);
    fclose(fp);
}
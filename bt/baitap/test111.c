#include <stdio.h>
#include <string.h>


#define FIRST_BYTE_TO_READ 10

char sFilename[64] = "D:/FA/txt/new 1.txt";
int i = 0;

int main()
{
    FILE* fp = NULL;
    unsigned char arr[32];

    fp = fopen(sFilename, "r");

    if (fp == NULL)
    {
        printf("\n cannot open file");
        return 0;
    }

    memset(arr, 0 , sizeof(arr));

    for (i = 0; i < FIRST_BYTE_TO_READ; i++)
    {
        fread(arr + i, sizeof(char), 1 , fp);
            
    }
    
    for (i = 0; i < FIRST_BYTE_TO_READ; i++)
    {
        printf("\n  0x%02X = %u = %c", arr[i], arr[i], arr[i]) ;
    }

    


    fclose(fp);
    return 0;

}
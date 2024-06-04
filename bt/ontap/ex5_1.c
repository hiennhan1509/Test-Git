#include <stdio.h>
#pragma pack(1)

float fVar = 3.14;

char *cByte = (char*) &fVar;

void main ()
{
    system("cls");
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        cByte = cByte + i ;
        printf ("%x ", *cByte);
    }
}
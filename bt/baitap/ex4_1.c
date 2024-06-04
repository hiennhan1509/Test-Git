#include <stdio.h>

float f = 5.1231456;
char* p1 = (char*)&f;


void main()
{   
    int i = 0;       
    for(i = 0; i < 4; i++)
    {
        *p1 = *(p1 + i);
        printf("%x ", *(p1+i));
    }

}
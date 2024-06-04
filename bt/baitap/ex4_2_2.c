#include <stdio.h>
#pragma pack(1)


struct 
{
    char c;
    long l;
    char str[17];
    short s;
}s1;

// char* p1 = (char*)&var;
int i = 0;

void main()
{   
    struct s1;
    printf("%x %x %x %x", &s1.c, &s1.l, &s1.str, &s1.s);

}


#include <stdio.h>
# pragma pack(1)


struct 
{
    char c;
    long l;
    char *str;
    short s;
}var;

// char* p1 = (char*)&var;
int i = 0;

void main()
{
    struct var;
    var.str = "afaf";
    printf("%x %x %x %x", &var.c, &var.l, &var.str, &var.s);
    printf("\n%s", var.str);
}


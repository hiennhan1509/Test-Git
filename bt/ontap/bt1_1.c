#include <stdio.h>

int func(int a)
{
    int UpperCase;
    UpperCase = a - 32;
    return UpperCase;
}

void main()
{
    int var;
    var = func(97);
    printf("%c",var);
    
}
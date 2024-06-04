#include <stdio.h>

void Add(int a, int b)
{
    printf("Add = %d\n", a+b);
}

void Sub(int a, int b)
{
    printf("Sub = %d\n", a-b);
}

void Mul(int a, int b)
{
    printf("Mul = %d\n", a*b);
}

void main()
{
    void (*FP_arr[])(int, int) = {Add, Sub, Mul};
    int a = 5, b = 10;

    for (int i = 0; i < 3; i++)
    {
        (*FP_arr[i])(a,b);
    }
    
}
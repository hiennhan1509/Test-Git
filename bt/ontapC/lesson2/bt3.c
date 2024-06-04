#include <stdio.h>

int giaithua(int x);

void main()
{
    printf("%d\n",giaithua(-3)); 
}


int giaithua(int x)
{
    int result = 1;
    if (x == 0)
    {
        return 1;
    }else if (x>0)
    {
        for (int i = 1; i <= x; i++) result *= i;
        return result;
    }else
    {
        printf("Nhap sai gia tri! ");
        return -1;
    }
}

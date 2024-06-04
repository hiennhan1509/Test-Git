#include <stdio.h>

int i = 1;
int giaithua = 1;
void gt();

void main()
{
    gt();
    printf("%d", giaithua);
}

void gt()
{       
    if (i <= 7)
    {
    giaithua = giaithua*i ;
    i++;
    gt();
    }
}
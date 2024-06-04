#include <stdio.h>

int a = 5;
int b = 11;
int i = 0;
int uc;
int tam;
void ucln();
void bcnn(int x, int y);

void main()
{
    ucln();
    bcnn(20,54);
}

void ucln()
{
    
    if(a>b)
    {   
        uc = a%b;
        while (uc != 0)
        {   
            a = b;
            b = uc;
            uc = a%b;
        }
    }else
    {   
        uc = b%a;
        while (uc != 0)
        {   
            b = a;
            a = uc;
            uc = b%a;
        }
    }

    printf("ucln = %d", a);
}

void bcnn(int x, int y)
{
    int flag = 0;
    flag = x * y;
    for (i = 2; i <= flag; i++)
    {
        if ((i % x == 0) && (i % y == 0 ))
        {
            break;
        }
    }
    printf("\nbcnn cua %d va %d = %d", x, y, i);
}
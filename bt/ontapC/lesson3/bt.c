#include <stdio.h>
int i = 1;
unsigned int result = 1;

void f_giaithua(int nGiaithua);
int main()
{
    f_giaithua(7);
    printf("%d",result);

}

void f_giaithua(int nGiaithua)
{   
    if (nGiaithua == 0)
    {
        return;
    }else if (nGiaithua>0)
    {
        result *= i;
        i ++;
    }

    if (i == nGiaithua)
    {
        return;
    }
    f_giaithua(nGiaithua); 
}

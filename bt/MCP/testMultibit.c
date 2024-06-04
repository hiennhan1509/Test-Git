#include <stdio.h>


void f_SetMultibit(unsigned int *iAddress, unsigned char iShiftToPos, unsigned int Mask ,unsigned int iValue)
{
    unsigned int temp = *iAddress;
    temp &= ~(Mask<<iShiftToPos);
    temp |= (iValue<<iShiftToPos);
    *iAddress = temp;
}

void main()
{
    unsigned int a = 0x5;
    f_SetMultibit(&a, 0, 0x7, 3);
    printf("%x",a);
}
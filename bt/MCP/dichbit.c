#include <stdio.h>

#define SET_BIT 1
#define CLEAR_BIT 0


void f_BitMaskRevision(unsigned int* iAddress, unsigned char iPosition, unsigned char iAction);

void main()
{

    unsigned int iNum = 215;
    unsigned char iPos = 3;
    f_BitMaskRevision(&iNum, iPos, SET_BIT);
    printf("%d\n", iNum);
}

void f_BitMaskRevision(unsigned int* iAddress, unsigned char iPosition, unsigned char iAction)
{
	if(iAction == 1)
	{
		*iAddress |= 1<<iPosition; /*Set bit at n Position = 1*/
	}else
	{
		*iAddress &= ~(1<<iPosition); /*Set bit at n Position = 0*/
	}
}
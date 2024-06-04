#include <stdio.h>
unsigned int f_ReadMultibit(volatile unsigned int *reg, unsigned char position, unsigned int mask);

void main()
{
	unsigned int a = 8165;
	unsigned int flag = 0;
	flag = f_ReadMultibit(&a, 4, 0xFF);

	printf("%x",flag);

}

unsigned int f_ReadMultibit(volatile unsigned int *reg, unsigned char position, unsigned int mask)
{
    unsigned int temp = *reg;
    temp = (temp>>position)&mask;
    return temp;
}
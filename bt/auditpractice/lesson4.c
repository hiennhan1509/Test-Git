#include <stdio.h>

static int a = 5;

int test()
{
    a = 10;
    printf("%d",a);
}

void main()
{
    // unsigned char a = 0x9D;
    // unsigned char b = 0;

    // // b = a&(0xFF>>5); //1001 1101 & 0000 0111 = 0x101
    // a = (a>>3)|(((a&(0xFF>>5))<<5)); // 0001 0011 | 1010 0000 = 1011 0011
    // printf("%02x", a);

    // char S[] = "abcd";
    // char c[] = {'a','b','c','d','\0'};

    // printf("%s\n",c);

    // S[2] = '\1';
    test();
    printf("%d", a);


}


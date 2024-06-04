#include <stdio.h>


unsigned char reverse_byte(char a)
{

  return ((a & 0x1)  << 7) | ((a & 0x2)  << 5) |
         ((a & 0x4)  << 3) | ((a & 0x8)  << 1) |
         ((a & 0x10) >> 1) | ((a & 0x20) >> 3) |
         ((a & 0x40) >> 5) | ((a & 0x80) >> 7);
}

void main()
{
    char i = 0;
    i = reverse_byte(23);
    printf("%x",i );
}
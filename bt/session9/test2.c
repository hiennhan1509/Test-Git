#include <stdio.h>
// #pragma pack(4)

struct struct1 //8 Byte ? 6 byte
{
    char a;
    short b;
    char c;
};

struct struct2 //12
{
    char a;
    int b;
    char c;
};

struct struct3 //16
{
    char a;
    double b;
    char c;
};

struct struct4 //12
{
    char a;
    double *b;
    char c;
};

struct struct5  //24
{
    char a;
    struct struct4 b;
    char c;
};
void main()
{
    printf("%d \n%d \n%d \n%d \n%d", sizeof(struct struct1), sizeof(struct struct2), sizeof(struct struct3), sizeof(struct struct4), sizeof(struct struct5));
}
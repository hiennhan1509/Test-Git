#include <stdio.h>

#define CUBE(x) x *x *x
#define SUM(x) x+x

// int a = 2;
// int arr[5] = {1, 2, 3, 4, 5};
// int i = 0;
// int j = 0;

// int x[10][10];

int x = 3;

void main()
{
    int y = 3;
    printf("++x = %d \n", SUM(++x));       /*++x + ++x*/ 
    printf("++y = %d \n", SUM(++y));       /*++y + ++y*/ 
    
    // printf("x+1 = %d \n", CUBE(x+1));
    // printf("y+1 = %d \n", CUBE(y+1));



    // int *y = x[ ++i, ++j ];
    // int a = x*++x;
    //  printf("%d ", ++x*++x*++x);

    // printf("%X ", y);
    // printf("%X ", x[i , j]);

    // char c[2] = {'\n','\0'};
    // char p[] = "\n";
    // printf("%s", c);
    // printf("%d", sizeof(p));
    
    
    // int a = 10;
    // int *p = &a;
    // printf("%x %x %d\n", &a, p, *p);
    // *p += 1;
    // //*p++ : dia chi + size of type
    // //*p += 1 gia tri + 1 = 11

    // printf("%x %x %d", &a, p, *p);
}
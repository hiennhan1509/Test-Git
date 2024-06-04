#include <stdio.h>


void fnc(int **p1)
{
    *p1 = 100000;
}

void main ()
{
    int a = 10;
    int *p = &a;
    int **q = &p;
    
    //fnc(q);
    printf("%d ", q);
    printf("%d ", &q);
    
}
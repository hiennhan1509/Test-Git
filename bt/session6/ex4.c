#include <stdio.h>

// int a[5] = {1,3,5,6,7};
// float a2[5] = {25,3,5,6,4};
// float b[7] = {5.1, 5.2, 5.3};
char c[10] = "THN1234";
char c1[10] = "2asdaf";
int i = 0;
int j = 0;

char *string[2] = {c,c1};
//char *arr[2] = {string[0], string[1]};
// arr[0] = &a;
// arr[1] = b;
// arr[2] = c;

void main()
{   
    printf("%x \n", &string[0]);

    for ( i = 0; i < 2; i++)
    {
        printf("%x \n",&string[i]);
    }
    
}    
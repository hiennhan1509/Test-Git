#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int i = 0;
void func(int x,...)
{
    char s1 [100];
    int arr[x];
    va_list argl;
    va_start (argl, x);

    for (i = 0; i<x; i++)
    {
        arr[i] = va_arg(argl, int);
        strcpy(s1, va_arg(argl, char*));
    }

    for(i=0;i<100;i++)
    {
        printf("%c", s1[i]);
    }
}


// float Averange (int x,...)
// {
//     float sum;
//     va_list arglist;
//     va_start (arglist, x);
//     for(i = 0; i<x; i++)
//     {
//         sum += va_arg(arglist, double);
//         printf("%.2f ", sum);
//     }
//     va_end(arglist);
//     return sum/x;
// }

void main()
{
    func(5, 1,3 , 5, 7, 10);
}




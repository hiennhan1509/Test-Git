#include <stdarg.h>
#include <stdio.h>




float diem_tb(int num,...)
{   

    va_list name;
    float sum = 0.0f;
    int i;
    va_start (name, num);
    
    for(i=0; i<num; i++)
    {
        sum += va_arg(name,float);
    }

    va_end(name);
    return sum/num;

}

int main ()
{
   printf("Average of = %f\n", diem_tb(4, 2.2f, 3.4f, 4.5f, 5.1f));
   printf("Average of = %f\n", diem_tb(3, 5.1f ,10.0f , 15.2f));
}
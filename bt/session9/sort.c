#include <stdio.h>

float arr[10] = {-1, -12, -13, -4, -15, -5, -6, -8, 3, 11};
int i = 0;
int indexofminvalue = 0;
int j = 0;
float temp = 0;

float *SelectionSort(float arr[10])
{
    float min;
    for (i = 0; i < 9; i++)
    {   
        min = arr[i];
        for (j = i + 1; j < 10; j++)
        {
            if (min > arr[j])
            {
                min = arr[j];
                indexofminvalue = j;
            }
        }

        if (arr[i] != min)
        {
            temp = arr[i];
            arr[i] = arr[indexofminvalue];
            arr[indexofminvalue] = temp;
        }
    }
    return arr;
}

void main()
{
    float *p;
    p = SelectionSort(arr);
    for (i = 0; i < 10; i++)
    {
        printf("%.2f \n", p[i]);
    }
}
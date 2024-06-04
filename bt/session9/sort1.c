#include <stdio.h>

float arr[10] = {21, 12, 13, 20, 15, 5, 6, 8 , 3 , 11}; //3 5 6 8 11 12 13 15 20 21
int i = 0;
int indexofmaxvalue = 0;
float temp = 0;

float* Sort(float arr[10])
{
    int j = 0;

    for(i = 0; i < 10; i++)
    {
        float min = arr[i];

        for ( j = i+1; j < 10; j++)
        {
            if(min>=arr[j])
            {
                min = arr[j];
                indexofmaxvalue = j;
            }            
        }
            if (min != arr[i])
            {
                temp = arr[i];
                arr[i] = arr[indexofmaxvalue];
                arr[indexofmaxvalue] = temp;                
            }
            
    }
    return arr;
}

void main()
{
    float *p;
    p = Sort(arr);
    for ( i = 0; i < 10; i++)
    {
        printf("%.2f \n", p[i]);
        
    }
    
}
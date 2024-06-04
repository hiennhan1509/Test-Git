#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>


/*********************************************************
                    Decleration
**********************************************************/

typedef struct
{
    unsigned short ID;
    unsigned char *FullName;
    unsigned char Age;
    unsigned char Gender;
    unsigned char *Classcode;
    float AverangeMark;

} Student;




/*********************************************************
                    Fibonaccy Recusion
**********************************************************/

int FibRec(int i, int arr[], int Numberofsequence)
{
    arr[i] = arr[i-2] + arr[i-1];
    if (i<Numberofsequence-1)
    {
        i++;
        FibRec(i,arr,Numberofsequence);
    }
}

/*********************************************************
                    Find Value Recusion
**********************************************************/

int FindValue(int arr[], int n, int value, int i)
{
    
    if(arr[i] == value)
    {
        printf("Value = %d at index %d", arr[i], i);
        return i;
    }
    
    if ((arr[i] != value)&&(i<n))
    {   
        i++;
        FindValue(arr, n, value, i);
    }

    if ((i==n) && (arr[i-1] != value))
    {
        printf("There is no value = %d", value);
        exit(-1);
    }
    

    return 0;
}


/*********************************************************
            Calc Averange with variable arguments
**********************************************************/

double CalcAverangeMark(int narg,...)
{
    int sum = 0;
    int i = 0;
    double avr = 0.0;
    va_list arglist;

    va_start(arglist, narg);
    for ( i = 0; i < narg; i++)
    {
        sum += va_arg(arglist,int);
    }
    va_end(arglist);
    
    avr = (double) sum/narg;
    return avr;
}


/*********************************************************
                        Main
**********************************************************/

void main()
{
    /*********Fibonaccy Rec*********/
    // unsigned int arr[10];
    // arr[0] = 1; arr[1] = 1;

    // int i = 2;
    // FibRec(i, arr,10);
    // for (i = 0; i < 10; i++)
    // {
    //     printf("%d ", arr[i]);
    // } 
    
    /*********Fibonaccy Rec*********/

    // unsigned int arr[] = {6,9,4,2,8,16,5,7};
    // int n = sizeof(arr)/4;
    // int i = 0;
    // FindValue(arr, n, 16, 0);

/**************************Variable argument (Calculate Mark)***********************/
    double AvrMArk = 0;
    AvrMArk = CalcAverangeMark(4, 7,6,5,4);
    printf("Avr = %.2f", AvrMArk);
}
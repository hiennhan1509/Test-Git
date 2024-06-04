#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SelectionSort(float arr[], int iSize);
void BubbleSort(float arr[], int iSize);
void InsertSort (float a[],int n);
void swap(float *x, float *y);

float arr[] = {-21, -12, -13, -20, -15, -5, -6, -8, -3, -11}; // 3 5 6 8 11 12 13 15 20 21
char sName[4][25] = {"Hien Nhan", "Tan Vuong", "Hoang Phuc", "Toan"};
int i = 0;
int indexofmaxvalue = 0;
int j = 0;
float temp = 0;
int iSizeArr = sizeof(arr) / 4;

char flag = 0;
char tempName[25];

void main()
{
    system("cls");
    //SelectionSort(arr,iSizeArr);
    //BubbleSort(arr, iSizeArr);
    InsertSort(arr,iSizeArr);
    for ( i = 0; i < iSizeArr; i++)
    {
        printf("%.2f, ", arr[i]);
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3 - i; j++)
        {
            
            flag = strcmp(sName[j], sName[j + 1]);
            if (flag > 0)
            {
                strcpy(tempName,sName[j]);
                strcpy(sName[j],sName[j+1]);
                strcpy(sName[j+1],tempName);
            }
        }
            
    }    
        

        for ( i = 0; i < 4; i++)
        {
                /* code */
            printf("%s \n", sName[i]);
        }
}

void SelectionSort(float arr[], int iSize)
{
    for (i = 0; i < iSize; i++)
    {
        float min = arr[i];

        for (j = i + 1; j < iSize; j++)
        {
            if (min >= arr[j])
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
}

void BubbleSort(float arr[], int iSize)
{
    for (i = 0; i < iSize; i++)
    {
        for (j = 0; j < iSize - 1 - i; j++) /* iSize - 1 - i, when completed 1 loop, the biggest element stay in last index  */
        {
            float min = arr[j];
            if (min > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void InsertSort (float a[],int n)
{
    int j;
    for(int i=1;i<n;i++)
    {
       j=i-1;
       temp=a[i];
       while(j >= 0 && temp < a[j])
       {
           a[j+1]=a[j];
           j--;
       }
       a[j+1]=temp; // Chèn
    }  
}



void swap(float *x, float *y)
{
    temp = *x;
    *x = *y;
    *y = temp;
}
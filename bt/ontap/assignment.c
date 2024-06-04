#include <stdio.h>
#include <stdlib.h>

int *iP1;
void InputData(int *iP1, int n);
void ClearData (int *iP1);
void PrintData(int *iP1, int n);
void MaxValue(int *iP1, int n);
void MinValue(int *iP1, int n);
void InsertValue(int *iP1, int n, int pos, int value);

void main()
{
    int *iP1;
    int n = 5;

    iP1 = (int*) malloc(n*sizeof(int));

    InputData(iP1, n);
    
    InsertValue(iP1, n, 3, 12);

    PrintData(iP1, n);

}


void InputData(int *iP1, int n)
{
    int i = 0;
    int k = 0;
    int flag = 0;
    for(i = 0; i < n; i++)
    {
        do
        {   
            flag = 0;

            printf("nhap phan tu thu %d = ", i+1);
            fflush(stdin);
            scanf("%d", &(iP1[i]));
            for(k = 0; k < n; k++)
            {    
                if((iP1[i] == iP1[k])&&(i != k))
                {
                    flag = 1;
                }
            }
        } while ((iP1[i]<1)||(iP1[i])>200||(flag==1));
    }
}

void PrintData(int *iP1, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {   
        if((iP1[i] >= 1) && (iP1[i]) < 200)
        {
        printf("Output element %dth = %d\n", i+1, iP1[i]);
        }else {
            printf("day trong\n");
            break;
        }
    }
}

void ClearData(int *iP1)
{
    system("cls");
}

void DeleteData(int *iP1, int pos)
{
    if((iP1[pos] > 1) && (iP1[pos] < 200))
    {
        iP1[pos] = 0;
    }else{
        printf("No element in pos %dth \n", pos + 1);
    }
}

void FindValue(int *iP1, int n, int x)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (iP1[i] == x)
        {
            printf("%d \n", i+1 );
        }else
        {
            printf("No element in pos %dth \n", i+1);
            break;
        }        
    }
}

void MaxValue(int *iP1, int n)
{
    int max = iP1[0];
    int i = 0;
    for(i = 0; i < n; i ++)
    {
        if(max < iP1[i])
        {
            max = iP1[i];
        }
    }
    printf("%d \n", max);
}

void MinValue(int *iP1, int n)
{
    int min = iP1[0];
    int i = 0;
    for(i = 0; i < n; i ++)
    {
        if(min > iP1[i])
        {
            min = iP1[i];
        }
    }
    printf("%d \n", min);
}


void InsertValue(int *iP1, int n, int pos, int value)
{
    int i = 0;
    iP1 = (int*)realloc(iP1, (n+1)*sizeof(int));
    
    {
        do
        {
            printf("Enter positon ");
            fflush(stdin);
            //scanf("%d", &pos);

        } while ((pos<0)||(pos>100));

        //printf("Enter value = ");
        //scanf("%d", value);

        for(i = n; i > pos; i--)
        {
            iP1[i] = iP1[i-1];
        }
        
        iP1[pos] = value;

        n++;
    }
    for ( i = 0; i < n; i++)
    {
        printf("%d ", iP1[i]);
    }
    

}
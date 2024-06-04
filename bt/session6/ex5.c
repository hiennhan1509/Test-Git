#include <stdio.h>

unsigned short i = 0;
unsigned short j = 0;
void FixedArg(int sum[2][2],int a1[2][2], int a2[2][2]);
void HalfFixedArg(int (*sum)[2], int (*a1)[2], int (*a2)[2], int Col);
void FlexArg(int **sum, int**a1, int **a2, int rows, int cols);

int main()
{
    // int arr1[2][2] = {{2,7},{3,9}};
    // int arr2[2][2] = {{3,8},{4,10}};
    // int sum[2][2];

    //FixedArg(sum, arr1, arr2);

    int arr1[2][2] = {{2,7},{3,9}};
    int arr2[2][2] = {{3,8},{4,10}};
    int arr3[5] = {2,3,4,5,6};    
    int sum[2][2];
    
    //HalfFixedArg(sum, arr1, arr2, Cols);


    int Cols = 2;
    int Rows = 2;
    int **ptrS = (int**)sum;
    int **ptra1 = (int**)arr1;
    int **ptra2 = (int**)arr2;

    FlexArg(ptrS, ptra1, ptra2, Rows, Cols);
    return 0;
}

void FixedArg(int sum[2][2],int a1[2][2], int a2[2][2])
{
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            sum[i][j] = a1[i][j] + a2[i][j];
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
}

void HalfFixedArg(int (*sum)[2], int (*a1)[2], int (*a2)[2], int Col)
{
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < Col; j++)
        {
            sum[i][j] = a1[i][j] + a2[i][j];
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
}

void FlexArg(int **p, int **a1, int **a2, int rows, int cols)
{
    int (*sum)[cols] = (int (*)[cols])p;
    int (*arr1)[cols] = (int (*)[cols])a1;
    int (*arr2)[cols] = (int (*)[cols])a2;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            sum[i][j] = arr1[i][j] + arr2[i][j];
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
}
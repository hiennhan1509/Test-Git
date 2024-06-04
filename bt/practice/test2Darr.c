#include <stdio.h>

void Input(int **p, int Row, int Col);
void Output(int **p, int Row, int Col);

void main()
{
    int arr[2][3];
    int **p = (int**)arr;    ;
    

    Input(p,2,3);
    Output(p,2,3);
}

// void Input(int (*arr)[3], int Row)
// {
//     for (int i = 0; i < Row; i++)
//     {
//         for ( int j = 0; j < 3; j++)
//         {
//             printf("Nhap n = ");
//             fflush(stdin);
//             scanf("%d",&arr[i][j]);
//         }
//     }
// }

// void Output(int (*arr)[3], int Row)
// {
//     for (int i = 0; i < Row; i++)
//     {
//         for ( int j = 0; j < 3; j++)
//         {
//             printf("%d \n",arr[i][j]);
//         }

//     }
// }

void Input(int **p, int Row, int Col)
{
    int(*arr)[Col] = (int(*)[Col])p;

    for (int i = 0; i < Row; i++)
    {
        for (int j = 0; j < Col; j++)
        {
            printf("Nhap n = ");
            fflush(stdin);
            scanf("%d", &arr[i][j]);
        }
    }
}

void Output(int **p, int Row, int Col)
{
    int(*arr)[Col] = (int(*)[Col])p;
    for (int i = 0; i < Row; i++)
    {
        for (int j = 0; j < Col; j++)
        {
            printf("%d \n", arr[i][j]);
        }
    }
}
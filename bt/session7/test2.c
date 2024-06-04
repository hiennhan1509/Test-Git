#include <stdio.h>

// FILE* fp;
// char arr[30] = "abcdefsgii33431418340138413513";

void PassMethod3(int** p, unsigned Rows, unsigned nCols)
{
    unsigned int i, j;
    int (*)a[nCols] = (int (*)[nCols])p;
    for (i = 0; i < Rows; i++)
    {
        for (j = 0; j < nCols; j++)
        {
            a[i][j] = i*nCols + j;
            printf("%d ", a[i][j]);

        }
    }
}


void main()
{
    // fp = fopen("text2.txt", "r+");

    // fgets(arr, 2, fp);
    // printf("%s", arr);

    int **p1;
    int Row = 2;
    int Col = 3;

    PassMethod3(p1,Row,Col);


}
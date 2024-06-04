#include <stdio.h>
#include <stdlib.h>

int *iP1;
// void InputData();
// void ClearData ();
// void PrintData();

void main()
{
    int *iP1 = (int*) malloc (sizeof(int)*5); /*allocate 100 elements type char */
    int i = 0;
    int flag = 0;
    int k = 0;

    for(i = 0; i < 5; i++)
    {
        do
        {   
            flag = 0;

            printf("nhap phan tu thu %d = ", i+1);
            fflush(stdin);
            scanf("%d", &(iP1[i]));
            for(k = 0; k < 5; k++)
            {    
                if((iP1[i] == iP1[k])&&(i != k))
                {
                    flag = 1;
                }
            }
        } while ((iP1[i]<1)||(iP1[i])>200||(flag==1));
    }    

    i = 0;
    for (i = 0; i < 5; i++)
    {
        printf("Output element %dth = %d\n", i+1, iP1[i]);
    }

    system ("cls");
    
    for (i = 0; i < 5; i++)
    {   
        if((iP1[i] < 1) || (iP1[i]) > 200)
        {
        printf("Output element %dth = %d\n", i+1, iP1[i]);
        }else {
            printf("day trong\n");
            break;
        }
    }

}




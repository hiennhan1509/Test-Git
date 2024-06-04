/*Tieu Hien Nhan*/
#include <stdio.h>  /*use for scanf, printf*/
#include <stdlib.h> /*use for dynamic allocate*/

int g_n = 5;
void InputData(float *p1, int n);
void PrintValue(float *p1, int n);
void InsertValue(float *p1, int n);

void main()
{   
    unsigned char cKey;
    float *fp = (float*)malloc(sizeof(float)*100);


    do{
        printf("Number Chain Management\n");
        printf("Press i to insert 1 float value to a specific index in the chain\n");
        printf("Press p to display all elements of the chain\n");
        printf("Press q to exit program\n");
        
        
        InputData(fp, g_n);
        printf("Enter key: ");
        fflush(stdin);
        scanf("%c",&cKey);

    

        switch (cKey)
        {
        case 'p':
            {
                PrintValue(fp, g_n);
            }
            break;
        
        case 'i':
            {
                InsertValue(fp, g_n);
            }
            break;
        case 'q':
            {
                exit(0);
            }
            break;
        default:
            {
                printf("Invalid key\n");
            }
        }

    }while(cKey < 0);

    free(fp);
}

/*Enter data*/
void InputData(float *p1, int n)
{
    int i = 0;
    for(i = 0; i < n; i++)
    {
        printf("Enter %dth element = ", i + 1);
        fflush(stdin);
        scanf("%f", &p1[i]); /*input value*/
    }
}

/*Insert value*/
void InsertValue(float *p1, int n)
{
    int i = 0;
    int iPos = 0; 
    float fValue;

    printf("Enter posion you want to insert = ");
    fflush(stdin);
    scanf("%f", &iPos);

    printf("Enter value you to to insert = ");
    fflush(stdin);
    scanf("%f", &fValue);

    for(i = n; i > iPos; i--)
    {
        p1[i] = p1[i-1];
    }

    p1[iPos] = fValue; /*Insert value to dessert posion*/
}



/*Print value*/
void PrintValue(float *p1, int n)
{
    int i = 0;
    for(i = 0; i <n; i++)
    {
        printf("%.2f ",p1[i]); /*Print value with 2 presion*/
    }
}
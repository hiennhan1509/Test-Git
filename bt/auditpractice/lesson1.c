#include <stdio.h>
#include <stdarg.h>

/*********************************************************
                    Decleration
**********************************************************/

typedef struct
{
    unsigned char egde1;
    unsigned char egde2;
    unsigned char egde3;
    unsigned char egde4;
}Shape;


/*********************************************************
                Change case of a character.
**********************************************************/

void ChangeCase(unsigned char* cChar)
{
    if ((*cChar >= 65) && (*cChar <= 90))
    {
        *cChar += 32;
    }else if ((*cChar >=97)&&(*cChar<=122))
    {
        *cChar -=32;
    }else
    {
        printf("Wrong character");
    }    
}

/*********************************************************
                    Swap Value
**********************************************************/

void SwapValue(unsigned char* a, unsigned char* b)
{
    unsigned char c;
    c = *a;
    *a = *b;
    *b = c;
}


/*********************************************************
                    Calculate Area shape
**********************************************************/

unsigned int CalcAreaShape(unsigned int NumberofEdges,...)
{   
    va_list valist;
    unsigned int i;
    unsigned int ValueArea = 0;

    va_start(valist,NumberofEdges);

    for ( i = 0; i < NumberofEdges; i++)
    {
        ValueArea += va_arg(valist, unsigned int);
    }
    va_end(valist);

    return ValueArea;
}



/*********************************************************
                            Main
**********************************************************/
void main()
{

    /**************************************************************************/
    /*****************************Change Case*********************************/
    // unsigned char cCh = 0;
    // printf("Enter character: ");
    // fflush(stdin);
    // scanf("%c",&cCh);
    // ChangeCase(&cCh);
    // printf("%c",cCh);
    /**************************************************************************/


    /**************************************************************************/
    /*****************************Swap Value***********************************/
    // unsigned char A = 6;
    // unsigned char B = 7;
    // SwapValue(&A,&B);
    // printf("%d %d", A, B);

    /**************************************************************************/

    /**************************************************************************/
    /*****************************Calculate Area/***********************************/
    unsigned int A = 6;
    unsigned int B = 7;
    unsigned int C = 8;
    unsigned int D = 9;
    unsigned int Area = 0;
    unsigned char numberoflist = 4;
    if (numberoflist >= 3)
    {
        Area = CalcAreaShape(numberoflist, A,B,C,D);
        printf("Area = %d ", Area);
    }
    
    /**************************************************************************/


}
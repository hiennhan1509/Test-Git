#include <stdio.h>
#include <stdlib.h>

int n1 = 0x99;
unsigned n2 = 0xAB;
int CheckSLbit1(int temp, int isizeN);
int CheckSKbit0(int temp, int iszeN);
int CheckPosition(int temp, int Pos);
int CountRange1(int temp, int isizeN);



void main()
{
    system("cls");
    int temp1 = n1;
    unsigned temp2 = n2;
    int Sn = sizeof(int)*8;
    int Numberofbit1 = 0;
    int Numberofbit0 = 0;
    int CheckPos = 0;
    int NumRangebit1 = 0;
    
    /*Number of bit 1*/
    Numberofbit1 = CheckSLbit1(temp2, Sn);
    printf("Numberofbit1 = %d \n", Numberofbit1);

    /*Number of bit 0*/
    Numberofbit0 = CheckSKbit0(temp2, Sn);
    printf("Numberofbit0 = %d \n", Numberofbit0);

    /*Check position whether equal 1 ?*/
    CheckPos = CheckPosition(temp2, 5);
    if (CheckPos == 1)
    {
        printf("at this Position = 1\n" );
    }else
    {
        printf("at this Position = 0\n" );
    }
    
    /*Count Range of bit 1*/
    NumRangebit1 = CountRange1(temp2, Sn);
    printf("Number of Range 1 = %d\n",NumRangebit1);
    

}


int CheckSLbit1(int temp, int isizeN)
{
    int count = 0;

    for (int i = 0; i < isizeN ; i++)
    {
        if ((temp & (0x1)) !=0)
        {
            count++;
        }
        temp = temp>>1 ; // temp>>=1;
    }
    return count;
}

int CheckSKbit0(int temp, int iszeN)
{
    int count = 0;

    for (int i = 0; i < iszeN ; i++)
    {
        if ((temp & (0x1)) == 0)
        {
            count++;
        }
        temp = temp>>1 ; // temp>>=1;
    }
    return count;
}

int CheckPosition(int temp, int Pos)
{
    int flag = 0;
    int mot = 0x1;
    mot <<= Pos;
    if ((temp&(0x1)) != 0)
    {
        flag = 1;
    }
    return flag;
}

int CountRange1(int temp, int isizeN)
{
    int status = 0;
    int count = 0;
    int flag = 1;

    for (int i = 0; i < isizeN; i++)
    {
        // if ((temp&(0x1)) != 0) //0xF5 = 11110101
        // {
        //     status = 1;
        // }
        // else{
        //     status = 0;
        // }
        status = ((temp&(0x1))!=0)?1:0;

        temp = temp >> 1;
        flag = ((temp&(0x1))!=0)?1:0;

        if ((status == 1) && (flag == 0))
        {
            count++;
            status = 0;
        }
        
    }
    return count;
    
}
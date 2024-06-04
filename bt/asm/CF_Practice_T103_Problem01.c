#include <stdio.h>

int groupsOfBits(unsigned int N);

int main()
{
    unsigned int N = 0;
    unsigned char nCount = 0;

    do
    {
        printf("Enter N == 0 to exit program\n\n");
        /*input until N>=0 && N<=10E8*/
        do
        {
            printf("Nhap N: ");
            fflush(stdin);
            scanf("%d", &N);
        } while ((N < 0) || (N > 10E8));

        nCount = groupsOfBits(N);
        printf("Groups of bit = %d\n", nCount);
        printf("\n\n\n\n\n\n\n\n\n");
    } while (N != 0);
    return 0;
}

int groupsOfBits(unsigned int N)
{
    char nFlag = 1;
    char nStatus = 0;
    char nCount = 0;
    unsigned char i = 0;
    char isize = sizeof(int) * 8;

    /*Count groups of bit 1*/
    for (i = 0; i < isize; i++)
    {
        if (N & (0x1) != 0)
        {
            nStatus = 1; /*when last bit = 1, status = 1*/
        }
        else
        {
            nStatus = 0;
        }

        N >>= 1;            /*Then shift right 1 to check next bit*/
        if (N & (0x1) != 0) /*If next bit = 1, nFlag = 1*/
        {
            nFlag = 1;
        }
        else
        {
            nFlag = 0;
        }

        if ((nStatus == 1) && (nFlag == 0)) /*If bit i th and bit (i+1)th is 1 and 0, count + 1*/
        {
            nCount++;
            nStatus = 0;
        }
    }
    return nCount;
}
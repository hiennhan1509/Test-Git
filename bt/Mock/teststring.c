#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int InputString(unsigned char *data);
int StringtoArray(unsigned char *sString, unsigned char *arr, unsigned int sLength);
unsigned char StringtoDec(unsigned char *arr, unsigned int count);

unsigned char g_cKey;

typedef struct
{
    char cType;
    unsigned char iByteCount;
    unsigned int iAddress;
    unsigned char *iData;
    unsigned char iChecksum;
} tSrec;

int main()
{
    unsigned char *ptr;
    int count;
    int Length = 0;
    int NbElementsofArr;
    unsigned int i = 0;

    do
    {
        printf("nhap key:");
        fflush(stdin);
        scanf("%c", &g_cKey);
        getchar();
        printf("\n");

        tSrec st1;
        ptr = (unsigned char *)malloc(1007);
        st1.iData = (unsigned char *)malloc(252);
        // unsigned char *arr = (unsigned char *)malloc(3);

        Length = InputString(ptr);
        count = StringtoArray(ptr, st1.iData, Length);

        for (i = 0; i <= count; i++)
        {
            printf("%d ", st1.iData[i]);
        }
        printf("\n");
        free(ptr);
        free(st1.iData);
    } while (g_cKey!='q');

}

int InputString(unsigned char *data)
{
    unsigned int i = 0;
    unsigned int itemp = 0;
    unsigned int sLength;

    printf("Enter sequence integer number: ");
    fgets(data, 1007, stdin);
    strtok(data, "\n"); // delete "\n"
    sLength = strlen(data);
    return sLength;
}

int StringtoArray(unsigned char *sString, unsigned char *iData, unsigned int sLength)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int count = 0;
    unsigned int CountNBofElements = 0;
    unsigned char *arr = (unsigned char *)malloc(3);

    for (i = 0; i < sLength; i++)
    {

        if (sString[i] != ',')
        {
            arr[count] = sString[i];
            arr[count + 1] = '\0';
            count++;
            if (count == 4)
            {
                printf("****************************\n");
                printf("Wrong Input Value at position %d\n", CountNBofElements + 1);

                return CountNBofElements;
            }
        }
        else
        {
            count = 0;
            CountNBofElements++;
        }

        iData[CountNBofElements] = StringtoDec(arr, count);
    }

    free(arr);
    return CountNBofElements;
}

unsigned char StringtoDec(unsigned char *arr, unsigned int count)
{
    unsigned short value = 0;

    switch (count)
    {
    case 1:
        value = arr[0] - 48;
        break;
    case 2:
        value = (arr[0] - 48) * 10 + (arr[1] - 48);
        break;
    case 3:
        value = (arr[0] - 48) * 100 + (arr[1] - 48) * 10 + (arr[2] - 48);
        break;

    default:
        break;
    }
    if (value > 255)
    {
        printf("****************************\n");
        printf("Wrong Input Value = %d \n(Please Input Value from 0 - 255) ", value);
        return -1;
    }

    return value;
}
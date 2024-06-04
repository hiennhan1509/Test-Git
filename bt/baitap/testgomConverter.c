#include <stdio.h> /*use for scanf, printf, fprintf, fread*/
#include <stdlib.h> /*use for malloc, clear console*/
#include <string.h> /*use for strlen()*/
#include <math.h> /*use for pow()*/

/*********************************************************************
                            Defination
**********************************************************************/
#define MAX_LENGTH_DATA_OF_S1 252
#define MAX_LENGTH_DATA_OF_S2 251
#define MAX_LENGTH_DATA_OF_S3 5
#define START_CHARACTER 'S'

/*********************************************************************
                            Declaration
**********************************************************************/

typedef struct
{
    char cType;
    unsigned char iByteCount;
    unsigned int iAddress;
    unsigned char *pData;
    unsigned char iChecksum;
} tSrec;

void DisplayMenu();
unsigned short InputFromKeyboard(unsigned char *pData);
unsigned short StringtoDecArray(unsigned char *pString, unsigned char *pData, unsigned int sLength);
unsigned char StringtoDec(unsigned char *arr, unsigned int count);
void ConvertoS3(tSrec Srecord, unsigned int nSizeofData, unsigned int *StartAddress, unsigned char *pData, FILE *fp);
unsigned char Checksum(tSrec Srecord);
unsigned short CalcSumAddress(unsigned int iAddress, unsigned char nNumberBytesofAddress);
unsigned int FindStartAddr(FILE *fp, tSrec Srecord);
unsigned char ChartoDec(unsigned char cChar);


/*********************************************************************
                            Global Variable
**********************************************************************/
unsigned char g_ckey;


/*********************************************************************
                            Main Function
**********************************************************************/

void main()
{
    unsigned int nStringLength = 0;
    unsigned int i = 0;
    unsigned int nCountNumbers = 0;
    unsigned char *pStringData = (unsigned char *)malloc(1007); // 1007 = 252*4 - 1
    unsigned char sFileName[50];
    unsigned int iStartAddress = 0;
    tSrec st1;
    st1.pData = (unsigned char *)malloc(252);
    nStringLength = InputFromKeyboard(pStringData);
    nCountNumbers = StringtoDecArray(pStringData, st1.pData, nStringLength);

    /*************************************************************
        Create Func Pointer, check opening file whether complete
    **************************************************************/
    FILE *fp = NULL;
    printf("\nEnter your file path: ");
    fgets(sFileName, 50, stdin);
    strtok(sFileName, "\n");

    printf("%s\n", sFileName);
    fp = fopen(sFileName, "a+");
    if (fp == NULL)
    {
        printf("\n cannot open file");
        return;
    }

    /****************************************************************
                        Read File to find address
    *****************************************************************/
    iStartAddress = FindStartAddr(fp, st1);

    ConvertoS3(st1, nCountNumbers, &iStartAddress, st1.pData, fp);

    free(pStringData);
    free(st1.pData);
    fclose(fp);
}

/*********************************************************************
**********************************************************************/

unsigned short InputFromKeyboard(unsigned char *pString)
{
    unsigned int i = 0;
    unsigned int itemp = 0;
    unsigned int sLength;

    printf("Enter sequence integer number: ");
    fgets(pString, 1007, stdin);
    strtok(pString, "\n"); // delete "\n"
    sLength = strlen(pString);
    return sLength;
}

unsigned short StringtoDecArray(unsigned char *pString, unsigned char *pData, unsigned int sLength)
{
    unsigned int i = 0;
    unsigned int nCountDigits = 0; /*number digits before "," */
    unsigned int nCountNBofElements = 0;
    unsigned char *pArr = (unsigned char *)malloc(3);

    for (i = 0; i < sLength; i++)
    {

        if (pString[i] != ',')
        {
            pArr[nCountDigits] = pString[i];
            pArr[nCountDigits + 1] = '\0';
            nCountDigits++;
            if (nCountDigits == 4)
            {
                printf("****************************\n");
                printf("Wrong Input Value at position %d\n", nCountNBofElements + 1);

                return nCountNBofElements + 1;
            }
        }
        else
        {
            nCountDigits = 0;
            nCountNBofElements++;
        }

        pData[nCountNBofElements] = StringtoDec(pArr, nCountDigits);
    }

    free(pArr);
    return nCountNBofElements + 1;
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

void ConvertoS3(tSrec Srecord, unsigned int nSizeofData, unsigned int *StartAddress, unsigned char *pData, FILE *fp)
{
    unsigned char i;
    unsigned char j;
    unsigned int nCount = 0;
    unsigned int nSizeofFile;
    unsigned char MaxLength = 0;

    if (nSizeofData <= MAX_LENGTH_DATA_OF_S3)
    {
        for (i = 0; i < nSizeofData; i++)
        {
            Srecord.pData[i] = *(pData + i);
        }

        Srecord.cType = '3';
        /* Value of Byte Count of S1 = Number bytes of (4 byte Address + size of Data (Max = 252 bytes) + 1 Byte Checksum*/
        Srecord.iByteCount = nSizeofData + 5;
        Srecord.iAddress = *StartAddress;
        Srecord.iChecksum = Checksum(Srecord);
        printf("%c%1c %02X %06X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
        for (i = 0; i < nSizeofData; i++)
        {
            printf(" %02X", Srecord.pData[i]);
        }
        printf(" %02X\n", Srecord.iChecksum);

        fseek(fp, 0, SEEK_END);
        nSizeofFile = ftell(fp);
        printf("\n%d \n", nSizeofFile);
        fprintf(fp, "%1c%1c%02X%08X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
        for (i = 0; i < nSizeofData; i++)
        {
            fprintf(fp, "%02X", Srecord.pData[i]);
        }
        fprintf(fp, "%02X\n", Srecord.iChecksum);
        Srecord.iAddress += Srecord.iByteCount - 5;
    }
    if (nSizeofData > MAX_LENGTH_DATA_OF_S3)
    {
        Srecord.iAddress = *StartAddress;

        while(nSizeofData > MAX_LENGTH_DATA_OF_S3)
        {   
            /****************************************************************************************************************/
            for (i = 0; i < MAX_LENGTH_DATA_OF_S3; i++)
            {
                Srecord.pData[i] = *(pData + nCount);
                nCount++;
            }

            Srecord.cType = '3';
            /* Value of Byte Count of S1 = Number bytes of (4 byte Address + size of Data (Max = 252 bytes) + 1 Byte Checksum*/
            Srecord.iByteCount = MAX_LENGTH_DATA_OF_S3 + 5; /*Calculate Byte count*/
            Srecord.iChecksum = Checksum(Srecord); /*Calculate Check sum*/


            /**********************************************************************************************/
            printf("%c%1c %02X %08X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
            for (i = 0; i < MAX_LENGTH_DATA_OF_S3; i++)
            {
                printf(" %02X", Srecord.pData[i]);
            }
            printf(" %02X", Srecord.iChecksum);
            /**********************************************************************************************/

            /*Print Srecord format to file*/
            fseek(fp, 0, SEEK_END);
            nSizeofFile = ftell(fp);
            fprintf(fp, "%1c%1c%02X%08X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
            for (i = 0; i < MAX_LENGTH_DATA_OF_S3; i++)
            {
                fprintf(fp, "%02X", Srecord.pData[i]);
            }
            fprintf(fp, "%02X\n", Srecord.iChecksum);
            /***********************************************************************************************/

            Srecord.iAddress += Srecord.iByteCount - 5; /*Address for next Srecord*/
            nSizeofData -= MAX_LENGTH_DATA_OF_S3; /**/
            
            /*Until nSize of Data*/
            if (nSizeofData < MAX_LENGTH_DATA_OF_S3)
            {
                for (i = 0; i < nSizeofData; i++)
                {
                    Srecord.pData[i] = *(pData + nCount);
                    nCount++;
                }

                Srecord.cType = '3';
                /* Value of Byte Count of S1 = Number bytes of (4 byte Address + size of Data (Max = 252 bytes) + 1 Byte Checksum*/
                Srecord.iByteCount = nSizeofData + 5;
                Srecord.iChecksum = Checksum(Srecord);
                printf("%c%1c %02X %06X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
                for (i = 0; i < nSizeofData; i++)
                {
                    printf(" %02X", Srecord.pData[i]);
                }
                printf(" %02X", Srecord.iChecksum);

                fseek(fp, 0, SEEK_END);
                nSizeofFile = ftell(fp);
                printf("\n%d \n", nSizeofFile);
                fprintf(fp, "%1c%1c%02X%08X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
                for (i = 0; i < Srecord.iByteCount - 5; i++)
                {
                    fprintf(fp, "%02X", Srecord.pData[i]);
                }
                fprintf(fp, "%02X\n", Srecord.iChecksum);
                Srecord.iAddress += Srecord.iByteCount - 5;
            }

        };
    }
}

unsigned char Checksum(tSrec Srecord) /*nNumber of data = Value of byte count - 3/4/5 */
{
    unsigned int i = 0;
    unsigned int iValueofSumData = 0;
    unsigned short iValueofSumAddress = 0;
    unsigned char nNumberBytesofAddress = 0;
    unsigned int nNumberBytesofData; /*Number bytes of data */
    unsigned int iSum;
    unsigned int iChecksum;

    switch (Srecord.cType)
    {
    case '0':
    {
        nNumberBytesofData = Srecord.iByteCount - 3; /*Number Bytes of Data = Value of ByteCount - 3 (2 Bytes Address + 1 Byte checksum)*/
        nNumberBytesofAddress = 2;                   /*S0: 2 Bytes Address*/
    }
    break;
    case '1':
    {
        nNumberBytesofData = Srecord.iByteCount - 3; /*Number Bytes of Data = Value of ByteCount - 3 (2 Bytes Address + 1 Byte checksum)*/
        nNumberBytesofAddress = 2;                   /*S2: 2 bytes of Address*/
    }
    break;
    case '2':
    {
        nNumberBytesofData = Srecord.iByteCount - 4; /*Number Bytes of Data = Value of ByteCount - 4 (3 Bytes Address + 1 Byte checksum)*/
        nNumberBytesofAddress = 3;                   /*S2: 3 bytes of Address*/
    }
    break;
    case '3':
    {
        nNumberBytesofData = Srecord.iByteCount - 5; /*Number Bytes of Data = Value of ByteCount - 5 (4 Bytes Address + 1 Byte checksum)*/
        nNumberBytesofAddress = 4;                   /*S3: 4 bytes of Address*/
    }
    break;
    case '4':
        break;
    case '5':
    {
        nNumberBytesofData = 0;
        nNumberBytesofAddress = 2; /*S5: 2 bytes of Address use to count sum of record*/
    }
    break;
    case '6':
    {
        nNumberBytesofData = 0;
        nNumberBytesofAddress = 3; /*S6: 3 bytes of Address use to count sum of record*/
    }
    break;
    case '7':
    {
        nNumberBytesofData = 0;
        nNumberBytesofAddress = 4; /*S7: 4 bytes of Address*/
    }
    break;
    case '8':
    {
        nNumberBytesofData = 0;
        nNumberBytesofAddress = 3; /*S8: 3 bytes of Address*/
    }
    break;
    case '9':
    {
        nNumberBytesofData = 0;
        nNumberBytesofAddress = 2; /*S9: 2 bytes of Address*/
    }
    break;
    default:
        break;
    }

    /*Calculate Sum of Address*/
    iValueofSumAddress = CalcSumAddress(Srecord.iAddress, nNumberBytesofAddress);

    /*Calculate Value of sum of Data*/
    for (i = 0; i < nNumberBytesofData; i++)
    {
        iValueofSumData += Srecord.pData[i];
    }

    /*Calculate sum*/
    iSum = Srecord.iByteCount + iValueofSumAddress + iValueofSumData;

    /*Calculate checksum*/
    iChecksum = 0xFF - (iSum & 0XFF);
    return iChecksum;
}

/*&FF to get value of the last byte, then shift right 8 bits to get value next byte and sum value*/
unsigned short CalcSumAddress(unsigned int iAddress, unsigned char nNumberBytesofAddress)
{
    unsigned short iValueofSumAddress = 0;
    unsigned int iTempValue = iAddress;
    unsigned char i = 0;
    for (i = 0; i < nNumberBytesofAddress; i++)
    {
        iValueofSumAddress += ((iTempValue >> (8 * i)) & 0xFF);
    }

    return iValueofSumAddress;
}

/*READ FILE TO FIND NEXT ADDRESS OF FILE*/

unsigned int FindStartAddr(FILE *fp, tSrec Srecord)
{
    unsigned int nSizeofFile = 0;
    unsigned char cType = 0;
    unsigned char cFindS = 0;
    unsigned char *cAddrArr = (unsigned char *)malloc(8);
    unsigned char *iAddrArr = (unsigned char *)malloc(8);
    unsigned char *cByteCount = (unsigned char *)malloc(2);
    unsigned char *iByteCount = (unsigned char *)malloc(2);
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned char nFlag = 0;

    fseek(fp, 0, SEEK_END);
    nSizeofFile = ftell(fp);
    

    for (i = 0; i <= nSizeofFile; i++)
    {
        fseek(fp, -i, SEEK_END);
        fflush(stdin);
        fscanf(fp, "%c", &cFindS);
        /*Find Character S*/
        if (cFindS == 'S')
        {   
            nFlag = 1; // Have 'S' Character in File
            /*Find Type*/
            fseek(fp, -i + 1, SEEK_END);
            fflush(stdin);
            fscanf(fp, "%c", &cType);
            Srecord.cType = ChartoDec(cType);
            /*Find Byte Count*/
            for (j = 0; j < 2; j++)
            {
                fseek(fp, -i + 2 + j, SEEK_END);
                fflush(stdin);
                fscanf(fp, "%c", &cByteCount[j]);
                iByteCount[j] = ChartoDec(cByteCount[j]);
            }
            Srecord.iByteCount = iByteCount[0] * 10 + iByteCount[1];

            switch (Srecord.cType)
            {
            case 1:
            {
                Srecord.iAddress = 0;
                for (j = 0; j < 4; j++)
                {
                    fseek(fp, -i + 4 + j, SEEK_END);
                    fflush(stdin);
                    fscanf(fp, "%c", &cAddrArr[j]);
                    iAddrArr[j] = ChartoDec(cAddrArr[j]);
                    Srecord.iAddress += (iAddrArr[j] & 0x0F) << 4 * (3 - j);
                }
                return (Srecord.iAddress + Srecord.iByteCount - 3);
            }
            break;

            case 2:
            {
                Srecord.iAddress = 0;
                for (j = 0; j < 6; j++)
                {
                    fseek(fp, -i + 4 + j, SEEK_END);
                    fflush(stdin);
                    fscanf(fp, "%c", &cAddrArr[j]);
                    iAddrArr[j] = ChartoDec(cAddrArr[j]);
                    Srecord.iAddress += (iAddrArr[j] & 0x0F) << 4 * (5 - j);
                }
                return (Srecord.iAddress + Srecord.iByteCount - 4);
            }
            break;

            case 3:
            {
                Srecord.iAddress = 0;
                for (j = 0; j < 8; j++)
                {
                    fseek(fp, -i + 4 + j, SEEK_END);
                    fscanf(fp, "%c", &cAddrArr[j]);
                    iAddrArr[j] = ChartoDec(cAddrArr[j]);
                    Srecord.iAddress += (iAddrArr[j] & 0x0F) << 4 * (7 - j);
                }
                return (Srecord.iAddress + Srecord.iByteCount - 5);
            }
            break;

            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                continue;
                break;

            default:
                break;
            }
        }
    }

    if (nFlag == 0) /*Don't have any Srecord in File --> Address start at 0*/
    {
        return 0;
    }
    
    free(cAddrArr);
    free(iAddrArr);
    free(cByteCount);
    free(iByteCount);
    return 0;
}

unsigned char ChartoDec(unsigned char cChar)
{
    unsigned char DecNumber = 0;
    if ((cChar >= '0') && (cChar <= '9'))
    {
        DecNumber = cChar - 48;
    }
    else if ((cChar >= 'A') && (cChar <= 'F'))
    {
        DecNumber = cChar - 55;
    }
    else
    {
        printf("Wrong Charecter!");
    }
    return DecNumber;
}

/*Display Menu*/
void DisplayMenu()
{   
    system("cls");
    printf("\n************************************************************************************************************\n");
    printf("\n                                          S-RECORD APPLICATION                                              \n");
    printf(" * FEATURE:\n\n");
    printf("  1. Form a sequence of integer values, which is input from keyboard to S-Records and add it to S-Record file.\n");
    printf("  2. Convert binary Data from a specific file to S-Records and add them to S-Record file.\n");
    printf("  3. Convert 1-1 from a normal binary file to an S-Record file.\n");
    printf("  4. Check corruption for an S-Record file.\n");
    printf("\n************************************************************************************************************\n\n");
    printf(" * OPTION MENU: \n\n");
    printf("  - PRESS '1' to use FEATURE 1.\n");
    printf("  - PRESS '2' to use FEATURE 2.\n");
    printf("  - PRESS '3' to use FEATURE 3.\n");
    printf("  - PRESS '4' to use FEATURE 4.\n");
    printf("  - Press 'q' to quit program.\n");
    printf("\n************************************************************************************************************\n\n");
}

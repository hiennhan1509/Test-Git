#include <stdio.h>  /*use for scanf, printf, fprintf, fread*/
#include <stdlib.h> /*use for malloc, clear console*/
#include <string.h> /*use for strlen()*/
#include <math.h>   /*use for pow()*/

/*********************************************************************
                            Defination
**********************************************************************/
#define START_CHARACTER 'S'
#define MAX_LENGTH_DATA_OF_S1 252
#define MAX_LENGTH_DATA_OF_S2 251
#define MAX_LENGTH_DATA_OF_S3 250

/*********************************************************************
                            Declaration
**********************************************************************/

typedef struct
{
    unsigned char cType;
    unsigned char iByteCount;
    unsigned int iAddress;
    unsigned char *pData;
    unsigned char cChecksum;
} tSrec;

/*Do Function 1,2,3,4*/
void DoFunc1();
void DoFunc2();
void DoFunc3();
void DoFunc4();

void DisplayMenu();
/*Function 1*/
unsigned short InputFromKeyboard(unsigned char *pData);
/*Enter File Path*/
void EnterFileName(unsigned char *sFileName);
/*Use to Convert from 1,2,3,... to 1 2 3 ...*/
unsigned short StringtoDecArray(unsigned char *pString, unsigned char *pData, unsigned int nStringLength);
/*Check how many digits before ',' and convert to DEC*/
unsigned char StringtoDec(unsigned char *arr, unsigned int count);

/*Converter S1 - S3*/
void ConvertoS1(tSrec Srecord, unsigned int nSizeofData, unsigned int *StartAddress, unsigned char *pData, unsigned int nIndexofArray, FILE *fp);
unsigned int ConvertoS2(tSrec Srecord, unsigned int nSizeofData, unsigned int *StartAddress, unsigned char *pData, unsigned int nIndexofArray, FILE *fp);
unsigned int ConvertoS3(tSrec Srecord, unsigned int nSizeofData, unsigned int *StartAddress, unsigned char *pData, unsigned int nIndexofArray, FILE *fp);

/*Calc Checksum for function 1, 2, 3*/
unsigned char Checksum(tSrec Srecord);
unsigned short CalcSumAddress(unsigned int iAddress, unsigned char nNumberBytesofAddress);

/*File Start Address for next Srecord*/
unsigned int FindStartAddr(FILE *fp, tSrec Srecord);
/*Read Data from Binary File*/
void ReadFileBinary(FILE *fp, unsigned char iArr[], unsigned int nSizeofFile);
/*Input Srecord*/
void InPutSrecord(unsigned char *sString);
/*Check Srecord just entered*/
unsigned char CheckChecksum(unsigned char *sString, unsigned short nStrlen);
unsigned char ChartoDec(unsigned char cChar);
unsigned char PairCharto1DEC(unsigned char cChar1, unsigned char cChar2);

/*********************************************************************
                            Global Variable
**********************************************************************/
unsigned char g_ckey;

/*********************************************************************
                            Main Function
**********************************************************************/

void main()
{

    do
    {
        DisplayMenu();
        printf("Enter your choice: ");
        fflush(stdin);
        scanf("%c", &g_ckey);
        getchar();

        switch (g_ckey)
        {
        /* Form a sequence of integer values, which is input from keyboard to S-Records and add it to S-Record file.*/
        case 'A': /*Feature 1*/
        case 'a':
        {
            DoFunc1();
        }
        break;
        /*Convert binary Data from a specific file to S-Records and add them to S-Record file*/
        case 'B': /*Feature 2*/
        case 'b':
        {
            DoFunc2();
        }
        break;
        /*Convert 1-1 from a normal binary file to an S-Record file*/
        case 'C': /*Feature 3*/
        case 'c':
        {
            DoFunc3();
        }
        break;
        /*Check corruption for a S-Record*/
        case 'D': /*Feature 4*/
        case 'd':
        {
            DoFunc4();
        }
        break;
        case 'Q':/*Exit program*/
        case 'q':
            g_ckey = 'Q';
            break;
        default:
        {
            printf("Invalid key!!\nPlease Enter again!\n");
            printf("\nPress any key to continue: ");
        }
        break;
        }

    } while (g_ckey != 'Q');

}

/******************************************************************************************************************************
                                                    Do Function 1
*******************************************************************************************************************************/
void DoFunc1()
{
    unsigned int i = 0;
    unsigned int nStringLength = 0; /*Length of Sequence. Example: 1,2,3 -> nStringLength = 5*/
    unsigned int nCountNumbers = 0; /*Number of numbers in Sequence. Example: 1,2,3 -> nCountNumbers = 3*/
    /*1 number maximum acceptable is 3 digits and 1 ',' ... And Maximum Length of Data is 252 */
    unsigned int iStartAddress = 0;
    unsigned char *pStringData = (unsigned char *)malloc(1007); /* Allocate 4*252 - 1 = 1007 (1 is of characte ',')*/
    unsigned char *sFileName = (unsigned char *)malloc(50);
    tSrec tSrec;

    tSrec.pData = (unsigned char *)malloc(252);
    nStringLength = InputFromKeyboard(pStringData);
    nCountNumbers = StringtoDecArray(pStringData, tSrec.pData, nStringLength);
    /*Create Func Pointer, check opening file whether complete*/
    FILE *fpFunc1 = NULL;
    memset(sFileName, 0, sizeof(sFileName));
    EnterFileName(sFileName);         /*Enter File path*/
    fpFunc1 = fopen(sFileName, "a+"); /* "a+" read file or write to End of File*/
    /*Check whether open file complete?*/
    if (fpFunc1 == NULL)
    {
        printf("\n cannot open file");
        printf("\nPress any key to continue: ");
        getchar();
        return;
    }

    iStartAddress = FindStartAddr(fpFunc1, tSrec); /*Read File to find address*/

    if ((iStartAddress >= 0x0000) && (iStartAddress < 0xFFFF))
    {
        ConvertoS1(tSrec, nCountNumbers, &iStartAddress, tSrec.pData, 0, fpFunc1); /*0 is Start index of Array contain Data*/
        printf("\nSaved Data to File");
        printf("\nPress any key to continue: ");
        getchar();
    }
    else if ((iStartAddress >= 0x10000) && (iStartAddress < 0xFFFFFF))
    {
        ConvertoS2(tSrec, nCountNumbers, &iStartAddress, tSrec.pData, 0, fpFunc1);
        printf("\nSaved Data to File");
        printf("\nPress any key to continue: ");
        getchar();
    }
    else if ((iStartAddress >= 0x1000000) && (iStartAddress < 0xFFFFFFFF))
    {
        ConvertoS3(tSrec, nCountNumbers, &iStartAddress, tSrec.pData, 0, fpFunc1);
        printf("\nSaved Data to File");
        printf("\nPress any key to continue: ");
        getchar();
    }
    else
    {
        printf("Address is exceed!!");
        printf("\nPress any key to continue: ");
        getchar();
    }

    fclose(fpFunc1);
    free(pStringData);
    free(tSrec.pData);
    free(sFileName);
}

void DoFunc2()
{
    unsigned int i = 0;
    unsigned char *sFileName = (unsigned char *)malloc(50);
    unsigned int iStartAddress = 0;
    tSrec tSrec;
    tSrec.pData = (unsigned char *)malloc(252);

    /*Create Func Pointer, check opening file whether complete*/
    FILE *fpFunc2 = NULL;
    unsigned int nSizeofBINFile = 0;
    memset(sFileName, 0, sizeof(sFileName));
    printf("Open Binary file to read\n");
    EnterFileName(sFileName);         /*Enter Binary File path */
    fpFunc2 = fopen(sFileName, "rb"); /*read binary type*/
    /*Check whether open file complete?*/
    if (fpFunc2 == NULL)
    {
        printf("\n cannot open file");
        printf("\nPress any key to continue: ");
        getchar();
        return;
    }
    fseek(fpFunc2, 0, SEEK_END);
    nSizeofBINFile = ftell(fpFunc2);
    unsigned char cTempArr[nSizeofBINFile]; /*initialize array to contain data from BIN file*/

    ReadFileBinary(fpFunc2, cTempArr, nSizeofBINFile); /*Read data from file to temp Array*/
    unsigned char *pTempARR = cTempArr;
    fclose(fpFunc2); /*After read, close file Binary*/

    /*Openfile in order to write data to Srecfile*/
    printf("Open Srecord file to write\n");
    EnterFileName(sFileName);         /*Enter File path*/
    fpFunc2 = fopen(sFileName, "a+"); /* "a+" read file or write to End of File*/
    /*Check whether open file complete?*/
    if (fpFunc2 == NULL)
    {
        printf("\n cannot open file");
        printf("\nPress any key to continue: ");
        getchar();
        return;
    }

    iStartAddress = FindStartAddr(fpFunc2, tSrec); /*Read Srecord File to find address for next Data*/

    if ((iStartAddress >= 0x0000) && (iStartAddress < 0xFFFF))
    {
        ConvertoS1(tSrec, nSizeofBINFile, &iStartAddress, pTempARR, 0, fpFunc2); /*0 is Start index of Array contain Data*/
        printf("\nSaved Data to File");
        printf("\nPress any key to continue: ");
        getchar();
    }
    else if ((iStartAddress >= 0x10000) && (iStartAddress < 0xFFFFFF))
    {
        ConvertoS2(tSrec, nSizeofBINFile, &iStartAddress, pTempARR, 0, fpFunc2);
        printf("\nSaved Data to File");
        printf("\nPress any key to continue: ");
        getchar();
    }
    else if ((iStartAddress >= 0x1000000) && (iStartAddress < 0xFFFFFFFF))
    {
        ConvertoS3(tSrec, nSizeofBINFile, &iStartAddress, pTempARR, 0, fpFunc2);
        printf("\nSaved Data to File");
        printf("\nPress any key to continue: ");
        getchar();
    }
    else
    {
        printf("Address is exceed!!");
        printf("\nPress any key to continue: ");
        getchar();
    }
    fclose(fpFunc2);
    free(sFileName);
    free(tSrec.pData);
}

void DoFunc3()
{
    unsigned int i = 0;
    unsigned char *sFileName = (unsigned char *)malloc(50);
    unsigned int iStartAddress = 0;
    tSrec tSrec;
    tSrec.pData = (unsigned char *)malloc(252);
    /*Create Func Pointer, check opening file whether complete*/
    FILE *fpFunc3 = NULL;
    unsigned int nSizeofFile = 0;

    memset(sFileName, 0, sizeof(sFileName));
    printf("Open Binary file to read\n");
    EnterFileName(sFileName);         /*Enter File path*/
    fpFunc3 = fopen(sFileName, "rb"); /*read binary type*/
    /*Check whether open file complete?*/
    if (fpFunc3 == NULL)
    {
        printf("\nCannot open file");
        printf("\nPress any key to continue: ");
        getchar();
        return;
    }

    fseek(fpFunc3, 0, SEEK_END);
    nSizeofFile = ftell(fpFunc3);
    unsigned char cTempArr[nSizeofFile]; /*initialize array to contain data from BIN file*/

    ReadFileBinary(fpFunc3, cTempArr, nSizeofFile); /*Read data from file to temp Array*/
    fclose(fpFunc3);                                /*After read, close file Binary*/

    /*Open File Srec in order to write*/
    printf("\nOpen Binary file to Write\n");
    EnterFileName(sFileName);        /*Enter File path*/
    fpFunc3 = fopen(sFileName, "w"); /* "w" write to start of File */
    if (fpFunc3 == NULL)
    {
        printf("\nCannot open file");
        printf("\nPress any key to continue: ");
        getchar();
        return;
    }

    iStartAddress = 0;                                                    /*Convert 1-1 and open file "w" type, start ardress = 0*/
    ConvertoS1(tSrec, nSizeofFile, &iStartAddress, cTempArr, 0, fpFunc3); /*Count of Arr from 0*/
    printf("\nSaved Data to File");
    printf("\nPress any key to continue: ");
    getchar();
    fclose(fpFunc3);
    free(sFileName);
    free(tSrec.pData);
}

void DoFunc4()
{
    unsigned short iLength = 0;
    unsigned char *sRecord = (unsigned char *)malloc(515); /*Max of Srecord = 514 characters and +1 for end Character */
    InPutSrecord(sRecord);
    iLength = strlen(sRecord);

    CheckChecksum(sRecord, iLength);

    printf("\nPress any key to continue: ");
    getchar();
    free(sRecord);
}

/******************************************************************************************************************************
                                                        Display Menu
*******************************************************************************************************************************/
void DisplayMenu()
{
    system("cls");
    printf("\n************************************************************************************************************\n");
    printf("\n                                          S-RECORD APPLICATION                                              \n");
    printf("\n************************************************************************************************************\n");
    printf(" * FEATURE:\n\n");
    printf("  1. Form a sequence of integer values, which is input from keyboard to S-Records and add it to S-Record file.\n");
    printf("  2. Convert binary Data from a specific file to S-Records and add them to S-Record file.\n");
    printf("  3. Convert 1-1 from a normal binary file to an S-Record file.\n");
    printf("  4. Check corruption for an S-Record file.\n");
    printf("\n************************************************************************************************************\n\n");
    printf(" * OPTION MENU: \n\n");
    printf("  - PRESS 'A' to use FEATURE 1.\n");
    printf("  - PRESS 'B' to use FEATURE 2.\n");
    printf("  - PRESS 'C' to use FEATURE 3.\n");
    printf("  - PRESS 'D' to use FEATURE 4.\n");
    printf("  - Press 'Q' to quit program.\n");
    printf("\n************************************************************************************************************\n\n");
}

/************************************************************************************************
                                    Input String type Data
*************************************************************************************************/
unsigned short InputFromKeyboard(unsigned char *pString)
{
    unsigned int i = 0;
    unsigned int itemp = 0;
    unsigned int sLength;

    printf("Enter sequence integer number: ");
    /*1 number maximum acceptable is 3 digits and 1 ',' ... And Maximum Length of Data is 252 */
    fgets(pString, 1007, stdin); /* Input Data 4*252 - 1 = 1007 (1 is of characte ',')*/
    strtok(pString, "\n");       // delete "\n"
    sLength = strlen(pString);
    return sLength; // Return String length consist of Number and ','
}

/************************************************************************************************
                                    Enter File Name
*************************************************************************************************/
void EnterFileName(unsigned char *sFileName)
{
    printf("\nEnter your file path: ");
    fgets(sFileName, 50, stdin);
    strtok(sFileName, "\n"); /*delete \n*/
}

/*****************************************************************************************************
                            Convert String to Number and save to Array
******************************************************************************************************/
unsigned short StringtoDecArray(unsigned char *pString, unsigned char *pData, unsigned int nStringLength)
{
    unsigned int i = 0;
    unsigned int nCountDigits = 0;                    /*number digits before ',' */
    unsigned int nCountNBofElements = 0;              /*use to count ',' */
    unsigned char *pArr = (unsigned char *)malloc(3); /*Allocate*/

    for (i = 0; i < nStringLength; i++)
    {
        if (pString[i] != ',') /*Find ',' in Sequence*/
        {
            pArr[nCountDigits] = pString[i]; /*remove ',' in String Sequence*/
            pArr[nCountDigits + 1] = '\0';   /*Assign '\0' to next elements to ensure don't have random value*/
            nCountDigits++;
            if (nCountDigits == 4) /*Count = 4 -> wrong because maximum data of unsigned char is 255 (3 digits)*/
            {
                printf("****************************\n");
                printf("Wrong Input Value at position %d\n", nCountNBofElements + 1);
                free(pArr);
                return nCountNBofElements + 1; /*number of ',' + 1 is number of Elements*/
            }
        }
        else
        {
            /*when = ',' -> there is new element after it*/
            nCountDigits = 0;
            nCountNBofElements++;
        }

        /*Assign value after transfer from digits to decimal*/
        pData[nCountNBofElements] = StringtoDec(pArr, nCountDigits);
    }

    free(pArr);
    return nCountNBofElements + 1;
}

/*********************************************************************
        Transfer digit of Number contain in array to DEC
**********************************************************************/
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

/***********************************************************************************************************************************************
                                                        Convert to S1 Srecord Format
************************************************************************************************************************************************/

void ConvertoS1(tSrec Srecord, unsigned int nSizeofData, unsigned int *StartAddress, unsigned char *pData, unsigned int nIndexofArray, FILE *fp)
{
    unsigned char i;
    unsigned char j;

    /*When Size of Data <=252*/
    if (nSizeofData <= MAX_LENGTH_DATA_OF_S1)
    {
        for (i = 0; i < nSizeofData; i++)
        {
            Srecord.pData[i] = *(pData + i);
        }

        Srecord.cType = '1';
        /* Value of Byte Count of S1 = Number bytes of (2 byte Address + size of Data (Max = 252 bytes) + 1 Byte Checksum*/
        Srecord.iByteCount = nSizeofData + 3;
        Srecord.iAddress = *StartAddress;      /*Address is found in File*/
        Srecord.cChecksum = Checksum(Srecord); /*Calculate checksum*/

        fseek(fp, 0, SEEK_END); /*put pointer in end of file*/

        /*Write Data after transfer srecord format to file*/
        fprintf(fp, "%1c%1c%02X%04X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
        for (i = 0; i < nSizeofData; i++)
        {
            fprintf(fp, "%02X", Srecord.pData[i]);
        }
        fprintf(fp, "%02X\n", Srecord.cChecksum);
        /*next address is = current address + size of Data */
        Srecord.iAddress += Srecord.iByteCount - 3;
    }

    /*When Size of data > 252*/
    if (nSizeofData > MAX_LENGTH_DATA_OF_S1)
    {
        Srecord.iAddress = *StartAddress;

        while (nSizeofData > MAX_LENGTH_DATA_OF_S1)
        {
            for (i = 0; i < MAX_LENGTH_DATA_OF_S1; i++)
            {
                Srecord.pData[i] = *(pData + nIndexofArray); /*Cut data when it > max length of s1*/
                nIndexofArray++;                             /*use to count position of data which is inputted*/
            }

            Srecord.cType = '1';
            /* Value of Byte Count of S1 = Number bytes of (2 byte Address + size of Data (Max = 252 bytes) + 1 Byte Checksum*/
            Srecord.iByteCount = MAX_LENGTH_DATA_OF_S1 + 3; /*Calculate Byte count*/
            Srecord.cChecksum = Checksum(Srecord);          /*Calculate Check sum*/
            /***********************************************************************************************/
            /*Write Srecord format to file*/
            fseek(fp, 0, SEEK_END);
            fprintf(fp, "%1c%1c%02X%04X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
            for (i = 0; i < MAX_LENGTH_DATA_OF_S1; i++)
            {
                fprintf(fp, "%02X", Srecord.pData[i]);
            }
            fprintf(fp, "%02X\n", Srecord.cChecksum);
            /***********************************************************************************************/

            Srecord.iAddress += Srecord.iByteCount - 3; /*Address for next Srecord*/
            nSizeofData -= MAX_LENGTH_DATA_OF_S1;       /*after do 1 loop, size of data - max length of S1*/

            /*Until Size of Data < max length And Address + length of Data are enough for 1 Srecord. Continue use format S1*/
            if ((nSizeofData < MAX_LENGTH_DATA_OF_S1) && (Srecord.iAddress + nSizeofData <= 0xFFFF))
            {
                for (i = 0; i < nSizeofData; i++)
                {
                    Srecord.pData[i] = *(pData + nIndexofArray);
                    nIndexofArray++;
                }

                Srecord.cType = '1';
                /* Value of Byte Count of S1 = Number bytes of (2 byte Address + size of Data (Max = 252 bytes) + 1 Byte Checksum*/
                Srecord.iByteCount = nSizeofData + 3;
                Srecord.cChecksum = Checksum(Srecord);
                /***********************************************************************************************/
                /*Write Srecord format to file*/
                fseek(fp, 0, SEEK_END);
                fprintf(fp, "%1c%1c%02X%04X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
                for (i = 0; i < Srecord.iByteCount - 3; i++)
                {
                    fprintf(fp, "%02X", Srecord.pData[i]);
                }
                fprintf(fp, "%02X\n", Srecord.cChecksum);
                /***********************************************************************************************/
                Srecord.iAddress += Srecord.iByteCount - 3;
            }

            /*If Address of Record S1 >= 0xFFFF or distance from current address to 0xFFFF is less than
            max length of Data of record S1 (252 character) -> use Record S2  */
            if ((Srecord.iAddress + nSizeofData > 0xFFFF) || (Srecord.iAddress >= 0XFFFF))
            {
                nSizeofData = ConvertoS2(Srecord, nSizeofData, &Srecord.iAddress, pData, nIndexofArray, fp);
            }
        };
    }
}

/***********************************************************************************************************************************************
                                                        Convert to S2 Srecord Format
************************************************************************************************************************************************/
unsigned int ConvertoS2(tSrec Srecord, unsigned int nSizeofData, unsigned int *StartAddress, unsigned char *pData, unsigned int nIndexofArray, FILE *fp)
{
    unsigned char i;
    unsigned char j;

    /*When Size of Data <=251*/
    if (nSizeofData <= MAX_LENGTH_DATA_OF_S2)
    {
        for (i = 0; i < nSizeofData; i++)
        {
            Srecord.pData[i] = *(pData + i);
        }

        Srecord.cType = '2';
        /* Value of Byte Count of S1 = Number bytes of (3 byte Address + size of Data (Max = 251 bytes) + 1 Byte Checksum*/
        Srecord.iByteCount = nSizeofData + 4;
        Srecord.iAddress = *StartAddress;      /*Address is found in File*/
        Srecord.cChecksum = Checksum(Srecord); /*Calculate checksum*/

        fseek(fp, 0, SEEK_END); /*put pointer in end of file*/

        /*Write Data after transfer srecord format to file*/
        fprintf(fp, "%1c%1c%02X%06X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
        for (i = 0; i < nSizeofData; i++)
        {
            fprintf(fp, "%02X", Srecord.pData[i]);
        }
        fprintf(fp, "%02X\n", Srecord.cChecksum);
        /*next address is = current address + size of Data */
        Srecord.iAddress += Srecord.iByteCount - 4;
    }

    /*When Size of data > 251*/
    if (nSizeofData > MAX_LENGTH_DATA_OF_S2)
    {
        Srecord.iAddress = *StartAddress;

        while (nSizeofData > MAX_LENGTH_DATA_OF_S2)
        {
            for (i = 0; i < MAX_LENGTH_DATA_OF_S2; i++)
            {
                Srecord.pData[i] = *(pData + nIndexofArray); /*Cut data when it > max length of s2*/
                nIndexofArray++;                             /*use to count position of data which is inputted*/
            }

            Srecord.cType = '2';
            /* Value of Byte Count of S2 = Number bytes of (3 byte Address + size of Data (Max = 251 bytes) + 1 Byte Checksum*/
            Srecord.iByteCount = MAX_LENGTH_DATA_OF_S2 + 4; /*Calculate Byte count*/
            Srecord.cChecksum = Checksum(Srecord);          /*Calculate Check sum*/
            /***********************************************************************************************/
            /*Write Srecord format to file*/
            fseek(fp, 0, SEEK_END);
            fprintf(fp, "%1c%1c%02X%06X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
            for (i = 0; i < MAX_LENGTH_DATA_OF_S2; i++)
            {
                fprintf(fp, "%02X", Srecord.pData[i]);
            }
            fprintf(fp, "%02X\n", Srecord.cChecksum);
            /***********************************************************************************************/

            Srecord.iAddress += Srecord.iByteCount - 4; /*Address for next Srecord*/
            nSizeofData -= MAX_LENGTH_DATA_OF_S2;       /*after do 1 loop, size of data - max length of S2*/

            /*Until Size of Data < max length And Address + length of Data are enough for 1 Srecord. Continue use format S2*/
            if ((nSizeofData < MAX_LENGTH_DATA_OF_S2) && (Srecord.iAddress + nSizeofData <= 0xFFFFFF))
            {
                for (i = 0; i < nSizeofData; i++)
                {
                    Srecord.pData[i] = *(pData + nIndexofArray);
                    nIndexofArray++;
                }

                Srecord.cType = '2';
                /* Value of Byte Count of S2 = Number bytes of (3 byte Address + size of Data (Max = 251 bytes) + 1 Byte Checksum*/
                Srecord.iByteCount = nSizeofData + 4;
                Srecord.cChecksum = Checksum(Srecord);
                /***********************************************************************************************/
                /*Write Srecord format to file*/
                fseek(fp, 0, SEEK_END);
                fprintf(fp, "%1c%1c%02X%06X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
                for (i = 0; i < Srecord.iByteCount - 4; i++)
                {
                    fprintf(fp, "%02X", Srecord.pData[i]);
                }
                fprintf(fp, "%02X\n", Srecord.cChecksum);
                /***********************************************************************************************/
                Srecord.iAddress += Srecord.iByteCount - 4;
            }

            /*If Address of Record S2 >= 0xFFFFFF or distance from current address to 0xFFFFFF is less than
            max length of Data of record S2 (251 character) -> use Record S3  */
            if ((Srecord.iAddress + nSizeofData > 0xFFFFFF) || (Srecord.iAddress >= 0XFFFFFF))
            {
                nSizeofData = ConvertoS3(Srecord, nSizeofData, &Srecord.iAddress, pData, nIndexofArray, fp);
            }
        };
    }
    return nSizeofData; /*To Stop Loop of S1*/
}

/***********************************************************************************************************************************************
                                                        Convert to S3 Srecord Format
************************************************************************************************************************************************/

unsigned int ConvertoS3(tSrec Srecord, unsigned int nSizeofData, unsigned int *StartAddress, unsigned char *pData, unsigned int nIndexofArray, FILE *fp)
{
    unsigned char i;
    unsigned char j;

    /*When Size of Data <=250*/
    if (nSizeofData <= MAX_LENGTH_DATA_OF_S3)
    {
        for (i = 0; i < nSizeofData; i++)
        {
            Srecord.pData[i] = *(pData + i);
        }

        Srecord.cType = '3';
        /* Value of Byte Count of S3 = Number bytes of (4 byte Address + size of Data (Max = 250 bytes) + 1 Byte Checksum*/
        Srecord.iByteCount = nSizeofData + 5;
        Srecord.iAddress = *StartAddress;      /*Address is found in File*/
        Srecord.cChecksum = Checksum(Srecord); /*Calculate checksum*/

        fseek(fp, 0, SEEK_END); /*put pointer in end of file*/

        /*Write Data after transfer srecord format to file*/
        fprintf(fp, "%1c%1c%02X%08X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
        for (i = 0; i < nSizeofData; i++)
        {
            fprintf(fp, "%02X", Srecord.pData[i]);
        }
        fprintf(fp, "%02X\n", Srecord.cChecksum);
        /*next address is = current address + size of Data */
        Srecord.iAddress += Srecord.iByteCount - 5;
    }

    /*When Size of data > 250*/
    if (nSizeofData > MAX_LENGTH_DATA_OF_S3)
    {
        Srecord.iAddress = *StartAddress;

        while (nSizeofData > MAX_LENGTH_DATA_OF_S3)
        {
            for (i = 0; i < MAX_LENGTH_DATA_OF_S3; i++)
            {
                Srecord.pData[i] = *(pData + nIndexofArray); /*Cut data when it > max length of s3*/
                nIndexofArray++;                             /*use to count position of data which is inputted*/
            }

            Srecord.cType = '3';
            /* Value of Byte Count of S3 = Number bytes of (4 byte Address + size of Data (Max = 250 bytes) + 1 Byte Checksum*/
            Srecord.iByteCount = MAX_LENGTH_DATA_OF_S3 + 5; /*Calculate Byte count*/
            Srecord.cChecksum = Checksum(Srecord);          /*Calculate Check sum*/
            /***********************************************************************************************/
            /*Write Srecord format to file*/
            fseek(fp, 0, SEEK_END);
            fprintf(fp, "%1c%1c%02X%08X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
            for (i = 0; i < MAX_LENGTH_DATA_OF_S3; i++)
            {
                fprintf(fp, "%02X", Srecord.pData[i]);
            }
            fprintf(fp, "%02X\n", Srecord.cChecksum);
            /***********************************************************************************************/

            Srecord.iAddress += Srecord.iByteCount - 5; /*Address for next Srecord*/
            nSizeofData -= MAX_LENGTH_DATA_OF_S3;       /*after do 1 loop, size of data - max length of S3*/

            /*Until nSize < max length -> End Record*/
            if (nSizeofData < MAX_LENGTH_DATA_OF_S3)
            {
                for (i = 0; i < nSizeofData; i++)
                {
                    Srecord.pData[i] = *(pData + nIndexofArray);
                    nIndexofArray++;
                }

                Srecord.cType = '3';
                /* Value of Byte Count of S3 = Number bytes of (4 byte Address + size of Data (Max = 250 bytes) + 1 Byte Checksum*/
                Srecord.iByteCount = nSizeofData + 5;
                Srecord.cChecksum = Checksum(Srecord);
                /***********************************************************************************************/
                /*Write Srecord format to file*/
                fseek(fp, 0, SEEK_END);
                fprintf(fp, "%1c%1c%02X%08X", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress);
                for (i = 0; i < Srecord.iByteCount - 5; i++)
                {
                    fprintf(fp, "%02X", Srecord.pData[i]);
                }
                fprintf(fp, "%02X\n", Srecord.cChecksum);
                /***********************************************************************************************/
                Srecord.iAddress += Srecord.iByteCount - 5;
                if (Srecord.iAddress >= 0xFFFFFFFF)
                {
                    printf("Warning full size of Srecord\n");
                    return -1;
                }
            }
        };
    }
    return nSizeofData; /*To Stop Loop of S2*/
}

/*********************************************************************
                        Calculate checksum
**********************************************************************/
unsigned char Checksum(tSrec Srecord)
{
    unsigned int i = 0;
    unsigned int iValueofSumData = 0;
    unsigned short iValueofSumAddress = 0;
    unsigned char nNumberBytesofAddress = 0;
    unsigned int nNumberBytesofData; /*Number bytes of data */
    unsigned int iSum;
    unsigned int cChecksum;

    /*nNumber of Data Bytes of S1/S2/S3 = Value of byte count - 3/4/5*/
    switch (Srecord.cType)
    {
    case '0':
    {
        /*Number Bytes of Data = Value of ByteCount - 3 (2 Bytes Address + 1 Byte checksum)*/
        nNumberBytesofData = Srecord.iByteCount - 3;
        nNumberBytesofAddress = 2; /*S0: 2 Bytes Address*/
    }
    break;
    case '1':
    {
        /*Number Bytes of Data = Value of ByteCount - 3 (2 Bytes Address + 1 Byte checksum)*/
        nNumberBytesofData = Srecord.iByteCount - 3;
        nNumberBytesofAddress = 2; /*S1: 2 bytes of Address*/
    }
    break;
    case '2':
    { /*Number Bytes of Data = Value of ByteCount - 4 (3 Bytes Address + 1 Byte checksum)*/
        nNumberBytesofData = Srecord.iByteCount - 4;
        nNumberBytesofAddress = 3; /*S2: 3 bytes of Address*/
    }
    break;
    case '3':
    {
        /*Number Bytes of Data = Value of ByteCount - 5 (4 Bytes Address + 1 Byte checksum)*/
        nNumberBytesofData = Srecord.iByteCount - 5;
        nNumberBytesofAddress = 4; /*S3: 4 bytes of Address*/
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
    cChecksum = 0xFF - (iSum & 0XFF);
    return cChecksum;
}

/****************************************************************************************
                        &0xFF to get value of the last byte,
            then shift right 8 bits to get value next byte and sum value
******************************************************************************************/
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

/*********************************************************************
                READ FILE TO FIND NEXT ADDRESS OF FILE
**********************************************************************/
unsigned int FindStartAddr(FILE *fp, tSrec Srecord)
{
    unsigned int nSizeofFile = 0;
    unsigned char cType = 0;
    unsigned char cFindS = 0;
    unsigned char *cAddrArr = (unsigned char *)malloc(8);   /*Contain character*/
    unsigned char *iAddrArr = (unsigned char *)malloc(8);   /*Contain value of Chacracter after transfer to DEC*/
    unsigned char *cByteCount = (unsigned char *)malloc(2); /*Contain character*/
    unsigned char *iByteCount = (unsigned char *)malloc(2); /*Contain value of Chacracter after transfer to DEC*/
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned char nFlag = 0; /*Use to identify 'S' character in file*/

    fseek(fp, 0, SEEK_END); /*put file poiter in end of file */
    nSizeofFile = ftell(fp);

    /*Traverse from end to start of file in order to find Address of nearest Srecord in File*/
    for (i = 0; i <= nSizeofFile; i++)
    {
        fseek(fp, -i, SEEK_END);
        fflush(stdin);
        fscanf(fp, "%c", &cFindS);
        /*Find Character S*/
        if (cFindS == 'S')
        {
            nFlag = 1;                   // Have 'S' Character in File
            fseek(fp, -i + 1, SEEK_END); /*Position of Type Byte*/
            fflush(stdin);
            fscanf(fp, "%c", &cType);
            Srecord.cType = ChartoDec(cType); /*Transfer Character to DEC*/
            /*Find Byte Count*/
            Srecord.iByteCount = 0;
            for (j = 0; j < 2; j++) /*Byte count is 1 byte, but Byte count in File is 2 bytes */
            {
                fseek(fp, -i + 2 + j, SEEK_END);
                fflush(stdin);
                fscanf(fp, "%c", &cByteCount[j]);
                iByteCount[j] = ChartoDec(cByteCount[j]);
                Srecord.iByteCount += (iByteCount[j]) << 4 * (1 - j); /*Calculate value of Byte count*/
            }

            switch (Srecord.cType)
            {
            case 1: /*If Byte type = 1 -> read 4 bytes Address in File*/
            {
                Srecord.iAddress = 0;
                for (j = 0; j < 4; j++)
                {
                    fseek(fp, -i + 4 + j, SEEK_END);
                    fflush(stdin);
                    fscanf(fp, "%c", &cAddrArr[j]);
                    iAddrArr[j] = ChartoDec(cAddrArr[j]);
                    /*Transfer digits in Array to Number*/
                    Srecord.iAddress += (iAddrArr[j]) << 4 * (3 - j);
                }

                free(cAddrArr);
                free(iAddrArr);
                free(cByteCount);
                free(iByteCount);
                return (Srecord.iAddress + Srecord.iByteCount - 3);
            }
            break;

            case 2: /*If Byte type = 2 -> read 6 bytes Address in File*/
            {
                Srecord.iAddress = 0;
                for (j = 0; j < 6; j++)
                {
                    fseek(fp, -i + 4 + j, SEEK_END);
                    fflush(stdin);
                    fscanf(fp, "%c", &cAddrArr[j]);
                    iAddrArr[j] = ChartoDec(cAddrArr[j]);
                    /*Transfer digits in Array to Number*/
                    Srecord.iAddress += (iAddrArr[j]) << 4 * (5 - j);
                }
                free(cAddrArr);
                free(iAddrArr);
                free(cByteCount);
                free(iByteCount);
                return (Srecord.iAddress + Srecord.iByteCount - 4);
            }
            break;

            case 3: /*If Byte type = 3 -> read 8 bytes Address in File*/
            {
                Srecord.iAddress = 0;
                for (j = 0; j < 8; j++)
                {
                    fseek(fp, -i + 4 + j, SEEK_END);
                    fscanf(fp, "%c", &cAddrArr[j]);
                    iAddrArr[j] = ChartoDec(cAddrArr[j]);
                    /*Transfer digits in Array to Number*/
                    Srecord.iAddress += (iAddrArr[j]) << 4 * (7 - j);
                }
                free(cAddrArr);
                free(iAddrArr);
                free(cByteCount);
                free(iByteCount);
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
        free(cAddrArr);
        free(iAddrArr);
        free(cByteCount);
        free(iByteCount);
        return 0;
    }

    free(cAddrArr);
    free(iAddrArr);
    free(cByteCount);
    free(iByteCount);
    return 0;
}

/*********************************************************************
            Transfer Char display on screen to Decimal
**********************************************************************/
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

/*********************************************************************
            READ FILE BINARY AND ASSIGN DATA TO ARRAY
**********************************************************************/
void ReadFileBinary(FILE *fp, unsigned char iArr[], unsigned int nSizeofFile)
{
    unsigned int i = 0;
    for (i = 0; i < nSizeofFile; i++)
    {
        fseek(fp, i, SEEK_SET);
        fflush(fp);
        fread(&iArr[i], 1, 1, fp);
    }
}

/*********************************************************************
                            Function 4
**********************************************************************/

/*********************************************************************
                /*INPUT RECORD TO CHECK CHECKSUM
**********************************************************************/
void InPutSrecord(unsigned char *sString)
{
    printf("Input Srecord to check: \n");
    fgets(sString, 515, stdin);
}

/*********************************************************************
        Calculate check sum and Compare with inputted CheckSum
**********************************************************************/
unsigned char CheckChecksum(unsigned char *sString, unsigned short nStrlen)
{
    unsigned int i = 0;
    unsigned char iSum = 0;
    unsigned char iChecksum = 0;

    if (sString[0] == 'S')
    {

        for (i = 2; i < nStrlen - 4; i += 2)
        {
            iSum += PairCharto1DEC(sString[i], sString[i + 1]);
        }

        iChecksum = 0xFF - (iSum & 0XFF);

        if (iChecksum == PairCharto1DEC(sString[i], sString[i + 1]))
        {
            printf("\nSrecord is True!!\n");
        }
        else
        {
            printf("\nSrecord is False!!\n");
        }
    }
    else
    {
        printf("Wrong Start Character!!\n");
        printf("\nPress any key to continue\n");
        getchar();
        return -1;
    }
}

/*********************************************************************
        Transfer a pair of Char to 1 Decimal
**********************************************************************/
unsigned char PairCharto1DEC(unsigned char cChar1, unsigned char cChar2)
{
    unsigned short iDEC = 0;
    unsigned char iChar1;
    unsigned char iChar2;
    iChar1 = ChartoDec(cChar1);
    iChar2 = ChartoDec(cChar2);
    iDEC = (iChar1 << 4) + iChar2;
    if ((iDEC > 255) && (iDEC < 0))
    {
        printf("\nWrong Iput!!\n");
        return -1;
    }
    return iDEC;
}

/*********************************************************************
                        End of S1
**********************************************************************/
/*I haven't done S9,8,7 yet*/
void EndOFS1(unsigned int StartAddr, FILE *fp, tSrec Srecord)
{
    Srecord.cType = '9';
    Srecord.iByteCount = 3;
    Srecord.iAddress = StartAddr;
    Srecord.cChecksum = Checksum(Srecord);
    fprintf(fp, "%1c%1c%02X%04X%02X\n", START_CHARACTER, Srecord.cType, Srecord.iByteCount, Srecord.iAddress, Srecord.cChecksum);
}

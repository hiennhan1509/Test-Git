#include <stdio.h>
#include <stdlib.h>

unsigned char g_iArr[100];
unsigned char *g_iP = g_iArr;
unsigned char g_cKey;
char g_sFileName[] = "ASM3_SortElements.txt";

void ClearData(unsigned char *pArr, unsigned char n);
void InputData(unsigned char *pArr);
void Print(unsigned char *pArr, unsigned char n);
void InsertData(unsigned char *pArr, unsigned char n);
void DeleteData(unsigned char *pArr, unsigned char n);
void FindValue(unsigned char *pArr, unsigned char n);
void GreatestValue(unsigned char *pArr, unsigned char n);
void SmallestValue(unsigned char *pArr, unsigned char n);
void SortDecremental(unsigned char *pArr, unsigned char n);
void swap(unsigned char *x, unsigned char *y);

void main()
{
    unsigned char i = 0;
    unsigned char nFlag = 0;
    unsigned char nN = 100;

    ClearData(g_iP, nN); /*set all elements = 0 (emty array)*/

    do
    {
        printf("Integer Array Management Program\n\n\n");
        printf("Press e or E to enter new Array\n");
        printf("Press c or C to clear data of the array\n");
        printf("Press p or P to print all elements of the array\n");
        printf("Press i or I to insert an element into the array at an index k\n");
        printf("Press d or D to delete an element at an index k\n");
        printf("Press f or F to find a value x in the array\n");
        printf("Press g or G to print the greatest value in the array\n");
        printf("Press s or S to print the smallest value in the array\n");
        printf("Press w or W to sort the array and write this array to file\n");
        printf("Press q or Q to quit program\n\n");
        printf("Enter your choice: ");
        fflush(stdin);
        scanf("%c", &g_cKey);
        printf("\n");

        switch (g_cKey)
        {
        case 'e':
        case 'E':
        {
            for (i = 0; i < nN; i++) /*Input n Elements*/
            {
                unsigned char j = 0;

                /*when Input Data smaller than 1 or greater than 200 or Check duplicate = 1, Enter value again*/
                do
                {
                    nFlag = 0;
                    printf("Enter number at index %d = ", i);
                    InputData(g_iP + i);
                    printf("\n");
                    for (j = 0; j < nN; j++)
                    {
                        if ((g_iP[i] == g_iP[j]) && (i != j)) /*check same elements in array*/
                        {
                            nFlag = 1; /*when value is duplicated, nflag = 1*/
                        }

                        if ((g_iP[i] < 1) || (g_iP[i] > 200) || (nFlag == 1))
                        {
                            printf("Invalid value! Please try again!\n");
                        }
                    }
                } while ((g_iP[i] < 1) || (g_iP[i] > 200) || (nFlag == 1)); /*when enter value < 1 or > 200 or duplicate, Enter value again*/
            }
            printf("\n");
            Print(g_iP, nN);
        }
        break;

        case 'c':
        case 'C':
        {
            ClearData(g_iP, nN);
            printf("Your array is emty\n");
        }
        break;

        case 'p':
        case 'P':
            Print(g_iP, nN);
            break;

        case 'i':
        case 'I':
        {
            InsertData(g_iP, nN);
            printf("\n");
            printf("Your array is: \n");
            Print(g_iP, nN);
        }
        break;

        case 'd':
        case 'D':
        {
            DeleteData(g_iP, nN);
            printf("\n");
            printf("Your array is: \n");
            Print(g_iP, nN);
        }
        break;

        case 'f':
        case 'F':
        {
            FindValue(g_iP, nN);
            printf("\n");
            printf("Your array is: \n");
            Print(g_iP, nN);
        }
        break;

        case 'g':
        case 'G':
        {
            GreatestValue(g_iP, nN);
            printf("\n");
            printf("Your array is: \n");
            Print(g_iP, nN);
        }
        break;

        case 's':
        case 'S':
        {
            SmallestValue(g_iP, nN);
            printf("\n");
            printf("Your array is: \n");
            Print(g_iP, nN);
        }
        break;

        case 'w':
        case 'W':
        {
            FILE *fp = NULL;
            fp = fopen(g_sFileName, "w"); /*Open file only write*/

            SortDecremental(g_iP, nN);
            printf("\n");
            printf("Your array is: \n");
            Print(g_iP, nN);

            for (i = 0; i < nN; i++)
            {
                if (g_iArr[i] != 0)
                {
                    fflush(fp);
                    fprintf(fp, "%d\n", g_iArr[i]);
                }
            }
            fclose(fp);
        }
        break;

        case 'q':
        case 'Q':
            g_cKey = 'q';
            break;

        default:
            printf("Invalid option!\n");
            break;
        }

        printf("\n\n\n\n\n\n\n\n\n\n\n");

    } while (g_cKey != 'q');
}

/*Clear all elements of array*/
void ClearData(unsigned char *pArr, unsigned char n)
{
    unsigned char i = 0;

    for (i = 0; i < n; i++)
    {
        pArr[i] = 0;
    }
}

/*Input Data from keyboard*/
void InputData(unsigned char *pArr)
{
    fflush(stdin);
    scanf("%d", pArr);
}

/*Print Data*/
void Print(unsigned char *pArr, unsigned char n)
{
    unsigned char i = 0;
    unsigned char nFlag = 0;
    for (i = 0; i < n; i++)
    {
        if (pArr[i] != 0)
        {
            printf("Value of index %d = %d\n", i, pArr[i]);
            nFlag = 1;
        }
        // else{
        //     printf("Value of index %d is emty\n", i);
        // }
    }

    if (nFlag == 0)
    {
        printf("Emty Array\n");
    }
}

/*Insert Data at position which input from keyboard and move array right from this position*/
void InsertData(unsigned char *pArr, unsigned char n)
{
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char nFlag = 1;
    unsigned int iK = 0;
    unsigned int iTemp = 0;
    unsigned char iVal = 0;
    unsigned char iStatus = 0;

    /*check whether array have any emty element*/
    for (i = 0; i < n; i++)
    {
        if (pArr[i] == 0)
        {
            nFlag = 0; // iflag = 0 -> Array has a emty element
            break;
        }
    }

    /*If Array have emty element -> Can insert*/
    if (nFlag == 0)
    {
        do
        {
            printf("Enter position you want to insert k (k = 0 - 99) = ");
            fflush(stdin);
            scanf("%d", &iK);
            if ((iK < 0) || (iK > 99))
            {
                printf("Out range of Array\n");
                printf("Enter again\n");
            }
        } while ((iK < 0) || (iK > 99)); /*Enter iK until 0 <= iK <= 99*/

        iTemp = iK; /*i dont know why use iK at below statments, then iK = 0 but iTemp don't change*/

        if (*(pArr + iTemp) == 0) /*check value at position iK whether emty? */
        {
            for (i = 99; i > iTemp; i--)
            {
                *(pArr + i) = *(pArr + i - 1); /*Push sequence backward from iK*/
            }

            /*when Input Data smaller than 1 or greater than 200 or Check duplicate = 1, Enter value again*/
            do
            {
                iStatus = 0;
                printf("\nEnter value you want to insert = ");
                InputData(&iVal);
                printf("\n");
                for (j = 0; j < 100; j++)
                {
                    if ((iVal == *(pArr + j)) && (iTemp != j))
                    {
                        iStatus = 1; /*when value is duplicated, iStatus = 1*/
                    }
                }

                if ((iVal < 1) || (iVal > 200) || (iStatus == 1))
                {
                    printf("Invalid value! Please try again!\n");
                }

            } while ((iVal < 1) || (iVal > 200) || (iStatus == 1));

            *(pArr + iTemp) = iVal; /*Assign value at position K*/
            printf("Insert at index %d = %d\n", iTemp, *(pArr + iTemp));
        }
        else
        {
            printf("\nThis position has value!\n");
            printf("Please choose other index!\n");
        }
    }
}

/*Delete element at position which input from keyboard*/
void DeleteData(unsigned char *pArr, unsigned char n)
{
    unsigned char i = 0;
    unsigned char iflag = 0;
    unsigned int iK = 0;

    /*Enter position iK until 0 <= iK <=99 */
    do
    {
        printf("Enter position you want to delete k (k = 0 - 99) = ");
        fflush(stdin);
        scanf("%d", &iK);
    } while ((iK < 0) || (iK > 99));

    if (pArr[iK] == 0)
    {
        printf("There is no value at index k\n");
    }
    else
    {
        printf("Delete value at index %d = %d\n", iK, pArr[iK]);
        pArr[iK] = 0;
    }
}

/*Find element in array which input from keyboard*/
void FindValue(unsigned char *pArr, unsigned char n)
{
    unsigned char i = 0;
    unsigned int iX = 0;
    unsigned char nFlag = 0;

    printf("Enter value you want to Find x = ");
    fflush(stdin);
    scanf("%d", &iX);

    for (i = 0; i < n; i++)
    {
        if (pArr[i] == iX)
        {
            printf("Value %d at index %d\n", iX, i);
            nFlag = 1; /*nFlag = 1 when found the same value. nFlag = 0 when didn't find any same value*/
            break; /*when found a value in array, terminate loop to program run more fast*/
        }
    }

    if (nFlag == 0)
    {
        printf("Don't have any value in array = %d \n", iX);
    }
}

/*Find smallest value in array*/
void GreatestValue(unsigned char *pArr, unsigned char n)
{
    unsigned char i = 0;
    unsigned char iMax = 0;
    unsigned char iIndex = 0;
    iMax = pArr[0];

    for (i = 1; i < n; i++)
    {
        if ((iMax < pArr[i]) && (pArr[i] != 0))
        {
            iIndex = i; /*Scan array and save index of max value*/
        }
    }

    if (pArr[iIndex] != 0)
    {
        iMax = pArr[iIndex]; /*assign max value at index just save*/
        printf("Greatest value = %d at index %d\n", pArr[iIndex], iIndex);
    }
}

/*Find smallest value in array*/
void SmallestValue(unsigned char *pArr, unsigned char n)
{
    unsigned char i = 0;
    unsigned char iMin = 0;
    unsigned char iIndex = 0;
    iMin = pArr[0];
    for (i = 1; i < n; i++)
    {
        if ((iMin > pArr[i]) && (pArr[i] != 0))
        {
            iIndex = i; /*Scan array and save index of min value*/
        }
    }

    if (pArr[iIndex] != 0)
    {
        iMin = pArr[iIndex]; /*assign min value at index just save*/
        printf("Smallest value = %d at index %d\n", pArr[iIndex], iIndex);
    }
}

/*Use selection sort to sort Decremental*/
void SortDecremental(unsigned char *pArr, unsigned char n)
{
    unsigned char i;
    unsigned char j;
    unsigned char iTemp;
    unsigned char nIndexofmaxvalue = 0;

    for (i = 0; i < n; i++)
    {
        unsigned char iMax = pArr[i];

        for (j = i + 1; j < n; j++)
        {
            if (iMax <= pArr[j])
            {
                iMax = pArr[j];       /*Find max value in array*/
                nIndexofmaxvalue = j; /*Scan array and save index of min value*/
            }
        }

        if (iMax != pArr[i])
        {
            swap(&pArr[i], &pArr[nIndexofmaxvalue]); /*pass by reference*/
        }
    }
}

/*Function to swap value*/
void swap(unsigned char *iX, unsigned char *iY)
{
    unsigned char iTemp;
    iTemp = *iX;
    *iX = *iY;
    *iY = iTemp;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h> /*use for isalnum()*/
#include <stdlib.h>

unsigned short InputID();
void InputFullName(char *sFN);
float InputAvrMark();
void CheckChar(char *sString);
char g_cKey;
/*Struct store information of student*/
struct tStudent
{
    unsigned short nID;
    char sFullName[25];
    float fAvrMark;
};

void SortName(int nArr, struct tStudent sv[]);

char sFileName[64] = "StudentManagement.bin";

int main()
{
    system("cls");
    FILE *fp = NULL;
    fp = fopen(sFileName, "ab+"); /*Open or create file*/
    struct tStudent tS;
    struct tStudent tReadSt[15]; /*15 is */

    printf("Student Management\n");
    printf("Press a to enter student information\n");
    printf("Press d to display student information\n");
    printf("Press s to search student information\n");
    printf("Press b to sort name as alphabet\n");
    printf("Press q to quit program\n");

    tS.nID = 0;

    do
    {
        printf("\nEnter your choice: ");
        fflush(stdin);
        scanf("%c", &g_cKey);
        fseek(fp, 0, SEEK_END);
        tS.nID = (int)ftell(fp) / 31; /*31 is size of 1 information of student*/

        switch (g_cKey)
        {
        case 'a':
        {
            /*Write information to file*/
            // printf("ID = %d \n", tS.nID);
            fwrite(&tS.nID, sizeof(short), 1, fp);
            /*Student Name*/
            InputFullName(tS.sFullName);
            fwrite(tS.sFullName, sizeof(char), 25, fp);
            /*Student Mark*/
            tS.fAvrMark = InputAvrMark();
            fwrite(&tS.fAvrMark, sizeof(float), 1, fp);
        }
        break;

        case 'd':
        {
            /*Read information from file*/
            unsigned short i = 0;
            fseek(fp, 0, SEEK_SET); /*pointer at position 0*/

            for (i = 0; i < tS.nID; i++)
            {
                fread(&tReadSt[i].nID, sizeof(short), 1, fp);
                memset(tReadSt[i].sFullName, 0, sizeof(tReadSt[i].sFullName));
                fread(tReadSt[i].sFullName, sizeof(char), 25, fp);
                fread(&tReadSt[i].fAvrMark, sizeof(float), 1, fp);
            }
            /*Display to screen*/
            for (i = 0; i < tS.nID; i++)
            {

                printf("%05d_%-24s_%.1f\n", tReadSt[i].nID, tReadSt[i].sFullName, tReadSt[i].fAvrMark);
            }
        }
        break;

        case 's':
        {
            unsigned nID = 0;
            printf("Enter student ID you want to find: ");
            fflush(stdin);
            scanf("%d", &nID);

            if (nID < tS.nID)
            {
                printf("%05d_%-24s_%.1f\n", tReadSt[nID].nID, tReadSt[nID].sFullName, tReadSt[nID].fAvrMark);
            }
            else
            {
                printf("The student with ID %05d doesn't exist!", nID);
            }
        }
        break;

        case 'b':
        {
            /*Read information from file*/
            unsigned short i = 0;
            fseek(fp, 0, SEEK_SET); /*pointer at position 0*/

            for (i = 0; i < tS.nID; i++)
            {
                fread(&tReadSt[i].nID, sizeof(short), 1, fp);
                memset(tReadSt[i].sFullName, 0, sizeof(tReadSt[i].sFullName));
                fread(tReadSt[i].sFullName, sizeof(char), 25, fp);
                fread(&tReadSt[i].fAvrMark, sizeof(float), 1, fp);
            }
            SortName(tS.nID, tReadSt);
            for (i = 0; i < tS.nID; i++)
            {
                printf("%05d_%-24s_%.1f\n", tReadSt[i].nID, tReadSt[i].sFullName, tReadSt[i].fAvrMark);
            }
        }

        case 'q':
            break;

        default:
        {
            printf("Invalid Option\n");
        }
        }

    } while (g_cKey != 'q');

    rewind(fp);
    fclose(fp);
    return 0;
}

/*Input student ID*/

/*Input Student Name*/
char flag = 0;
void InputFullName(char *sFN)
{
    do
    {
        flag = 1; /*when check is char or space --> flag = 1*/
        printf("Enter Student Full Name: ");
        fflush(stdin);
        gets(sFN);

        while (strlen(sFN) > 25)
        {
            printf("Name is too long, please Enter Name again: ");
            fflush(stdin);
            gets(sFN);
        }
        CheckChar(sFN);

    } while (flag == 0);
}

/*Input student Mark*/
float InputAvrMark()
{
    float fAvrM;
    do
    {
        printf("Enter Student Mark: ");
        fflush(stdin);
        scanf("%f", &fAvrM);
    } while ((fAvrM < 0) || (fAvrM > 10));

    return fAvrM;
}

/*check String whether is alphabet and space*/
void CheckChar(char *sString)
{
    char isize = strlen(sString);
    char Check = 1;
    int i = 0;
    for (i = 0; i < isize; i++)
    {

        Check = isalnum(sString[i]);
        if (Check == 0)
        {
            flag = 0;
        }
        if (sString[i] == 32)
        {
            flag = 1;
        }
    }
}

void SortName(int nArr, struct tStudent sv[])
{
    int i = 0;
    int j = 0;
    char status = 0;
    struct tStudent tempstruct;

    for (i = 0; i < nArr - 1; i++)
    {
        for (j = i + 1; j < nArr; j++)
        {
            status = strcmp(sv[i].sFullName, sv[j].sFullName);
            if (status > 0)
            {
                tempstruct = sv[i];
                sv[i] = sv[j];
                sv[j] = tempstruct;
            }
        }
    }
}

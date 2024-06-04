#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define nSTUDENT 3 /*number of student want to enter*/

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

char sFileName[64] = "StudentManagement.bin";

int main()
{
    FILE *fp = NULL;
    fp = fopen(sFileName, "ab+"); /*Open or create file*/
    struct tStudent tS;
    struct tStudent tReadSt[nSTUDENT];

    printf("Student Management\n");
    printf("Press a to enter student information\n");
    printf("Press d to display student information\n");
    printf("Press s to search student information\n");
    printf("Press q to quit program\n");

    tS.nID = 0;

    do
    {
        printf("\nEnter your choice: ");
        fflush(stdin);
        scanf("%c", &g_cKey);

        switch (g_cKey)
        {
        case 'a':
        {
            /*Write information to file*/
            /*Auto increase 1 for ID*/
            fwrite(&tS.nID, sizeof(short), 1, fp);
            tS.nID++;
            /*Student Name*/
            InputFullName(tS.sFullName);
            
            fwrite(tS.sFullName, sizeof(char), 24, fp);
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
            for (i = 0; i < nSTUDENT; i++)
            {
                fread(&tReadSt[i].nID, sizeof(short), 1, fp);
                memset(tReadSt[i].sFullName, 0, sizeof(tReadSt[i].sFullName));
                fread(tReadSt[i].sFullName, sizeof(char), 24, fp);
                fread(&tReadSt[i].fAvrMark, sizeof(float), 1, fp);
            }
            /*Display to screen*/
            for (i = 0; i < nSTUDENT; i++)
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

            if (nID < nSTUDENT)
            {
                printf("%05d_%-24s_%.1f\n", tReadSt[nID].nID, tReadSt[nID].sFullName, tReadSt[nID].fAvrMark);
            }
            else
            {
                printf("The student with ID %05d doesn't exist!", nID);
            }
        }
        break;

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
        flag = 1;
        printf("Enter Student Full Name: ");
        fflush(stdin);
        gets(sFN);
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


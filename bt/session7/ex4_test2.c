#include <stdio.h>
#include <string.h>

char sFileName[] = "rw2.bin";
unsigned int InputID();
void InputFullName(char* cFName);
float InputAverangeMark();


unsigned short i = 0;
unsigned short n = 3;

struct student
{
    unsigned int iID;
    char sFullName[24];
    float fAverangeMark;
};

int main()
{   
    FILE* fp = NULL;
    struct student sv;
    struct student sv1[n];
    char ckey;
    unsigned char clength[n];

    fp = fopen(sFileName, "wb+");

    /*write to file*/
    do
    {
        /*enter student ID*/
        fflush(fp);
        do{
            fflush(fp);
            sv.iID = InputID();

        }while((sv.iID) < 1 || (sv.iID) > 60000);

        fwrite(&sv.iID, sizeof(short), 1 , fp);

        /*enter student name*/

        memset(sv.sFullName, 0, sizeof(sv.sFullName));
        InputFullName(sv.sFullName);
        fwrite(sv.sFullName, sizeof(char), 24, fp);

        /*enter student Mark*/
        do{
            fflush(fp);
            sv.fAverangeMark = InputAverangeMark();

        }while((sv.fAverangeMark) < 0 || (sv.fAverangeMark) > 10);

        fwrite(&sv.fAverangeMark, sizeof(float), 1 , fp);
        printf("Do you want to input next student (Y/N): ");
        fflush(stdin);
        scanf("%c",&ckey);

        if(ckey == 'n')
        {
            ckey -=  32;
        }

        if (ckey == 'y' )
        {
            ckey -= 32;
        }

        i++;
        
    }while((i<n)&&(ckey!='N'));
    
    /*Read data from file*/
    int step = 0;
    int pos = 0;

    fseek(fp,step,SEEK_SET);
    for (i = 0; i < n; i++)
    {   
        fread(&sv1[i].iID, sizeof(short), 1, fp);
        memset(sv1[i].sFullName, 0 , sizeof(sv1[i].sFullName));
        fread(&sv1[i].sFullName, sizeof(char), 24, fp);
        fread(&sv1[i].fAverangeMark, sizeof(float), 1, fp);
    }

    for ( i = 0; i < n; i++)
    {
        printf("%05d %s %05.2f\n", sv1[i].iID, sv1[i].sFullName, sv1[i].fAverangeMark);
    }
    

    rewind(fp);
    fclose(fp);

}

unsigned int InputID()
{
    unsigned int ID = 0;
    printf("\nEnter student ID: ");
    fflush(stdin);
    scanf("%d",&ID);
    return ID;
}

void InputFullName(char* cFName)
{
    printf("Enter student name: ");
    fflush(stdin);
    gets(cFName);
}

float InputAverangeMark()
{
    float fmark = 0;
    printf("Enter student mark: ");
    fflush(stdin);
    scanf("%f",&fmark);
    return fmark;
}
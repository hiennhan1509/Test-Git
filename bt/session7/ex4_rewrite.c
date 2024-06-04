#include <stdio.h>
#include <string.h>

char sFileName[] = "rw2.bin";
unsigned short InputID();
void InputFullName(char* cFName);
float InputAverangeMark();


unsigned short i = 0;
unsigned short n = 3;

struct student
{
    unsigned short iID;
    char sFullName[24];
    float fAverangeMark;
};

int main()
{   
    FILE* fp = NULL;
    struct student sv[n];
    struct student sv1[n];
    char ckey;


    fp = fopen(sFileName, "wb+");

    /*write to file*/
    do
    {
        /*enter student ID*/
        fflush(fp);
        sv[i].iID = InputID();
        fwrite(&sv[i].iID, sizeof(short), 1 , fp);

        /*enter student name*/
        InputFullName(sv[i].sFullName);
        fwrite(sv[i].sFullName, sizeof(char), 24, fp);

        /*enter student Mark*/
        fflush(fp);
        sv[i].fAverangeMark = InputAverangeMark();
        fwrite(&sv[i].fAverangeMark, sizeof(float), 1 , fp);
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

    for (i = 0; i < n; i++)
    {   

        fseek(fp,step,SEEK_SET);
        fread(&sv1[i].iID, sizeof(short), 1, fp);
        memset(&sv1[i].sFullName, 32 , sizeof(sv1[i].sFullName));
        fread(&sv1[i].sFullName, sizeof(char), 24, fp);

        fread(&sv1[i].fAverangeMark, sizeof(float), 1, fp);
        step += 30;
    }

    for ( i = 0; i < n; i++)
    {
        printf("%05d %s %05.2f\n", sv1[i].iID, sv1[i].sFullName, sv1[i].fAverangeMark);
    }
    

    rewind(fp);
    fclose(fp);

}

unsigned short InputID()
{
    unsigned short ID = 0;
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
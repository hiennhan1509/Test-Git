#include <stdio.h>
#include <string.h>

char sFileName[64] = "rw1.bin";
unsigned short InputID();
void InputFName(char *FullName);
float InputMark();

int i = 0;
unsigned char length = 0;

struct tStudent
{
    unsigned short ID;
    char cFullName[24];
    float fAM;
};


int main()
{   
    FILE* fp = NULL;
    struct tStudent sv;
    struct tStudent Nhan;
    
    unsigned short rID[5];
    char rcFullName[24];
    float rfAM;


    fp = fopen(sFileName,"wb+");
    if (fp == NULL)
    {
        printf("cannot open file");
        return 0;
    }

    /*student ID*/
    sv.ID = InputID();
    fwrite(&sv.ID, sizeof(short), 1, fp);   


    /*student name*/
    InputFName(sv.cFullName);
    fwrite(sv.cFullName, sizeof(char), 24 , fp);

    /*student mark*/
    sv.fAM = InputMark();


    /*read from file*/
    /*read ID*/
    fseek(fp,0, SEEK_SET);
    fread(&sv.ID, sizeof(short) , 1 , fp);
    printf("%d ", sv.ID);

    /*read Name*/

    memset(sv.cFullName, 0 , sizeof(sv.cFullName));
    fread(sv.cFullName, sizeof(sv.cFullName), 1, fp);
    printf("%s ",sv.cFullName);

    /*read Mark*/

    fread(&sv.fAM, sizeof(float), 1, fp);
    printf("%05.2f ",sv.fAM);

    rewind(fp);
    fclose(fp);
    return 0;
}

unsigned short InputID()
{
    unsigned short ID = 0;
    printf("\nEnter student ID: ");
    fflush(stdin);
    scanf("%d", &ID);

    return ID;
}

void InputFName(char *FullName)
{
    
    printf("\nEnter student Full Name: ");
    fflush(stdin);
    gets(FullName);

}

float InputMark()
{
    
    float mark = 0;
    printf("\nEnter student mark: ");
    scanf("%f", &mark);

    return mark;
}
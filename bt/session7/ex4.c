#include <stdio.h>
#include <string.h>

char sFileName[64] = "ghi.txt";
unsigned short InputID();
void InputFName(char *FullName);
float InputMark();

int i = 0;

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
    char arr[24];

    fp = fopen(sFileName,"w+");
    if (fp == NULL)
    {
        printf("cannot open file");
        return 0;
    }

    unsigned short Id=0;
    /*student ID*/
    // fputs("Student ID: ", fp);
    sv.ID = InputID();
    fprintf(fp,"%5d", sv.ID);
    fseek(fp,0,SEEK_SET);
    fgets(&Id, 2, fp);
    //fscanf(fp,"%d", &Id);
    printf("%s ", Id);
    
    /*student name*/
    //fputs("Student name: ", fp);
    InputFName(sv.cFullName);
    fputs(sv.cFullName, fp);
    //fputc(10, fp);

    memset(arr,0,sizeof(arr));
    fgets(arr ,sizeof(arr), fp);
    printf("%s ", arr);
    /*student mark*/
    //fputs("Student mark: ", fp);
    //.fAM = InputMark();
    //fprintf(fp, "%.2f", sv.fAM);
    //fputc(10, fp);
    return 0;
}

unsigned short InputID()
{
    unsigned short ID = 0;
    printf("\nEnter student ID: ");
    fflush(stdin);-
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
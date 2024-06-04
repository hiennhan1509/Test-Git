#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************************************
                    Decleration
**********************************************************/

typedef struct
{
    unsigned short ID;
    unsigned char *FullName;
    unsigned char Age;
    unsigned char Gender;
    unsigned char *Classcode;
    float AverangeMark;

}Student;

/*********************************************************
                    Input Function
**********************************************************/
void InputStudent(Student *st)
{   
    printf("Enter Student ID: ");
    fflush(stdin);
    scanf("%d", &(st->ID));
    printf("\n");
    
    // st->FullName = (unsigned char*) malloc(26);

    printf("Enter Student Name: ");
    fflush(stdin);
    fgets(st->FullName, 26 ,stdin);
    strtok(st->FullName,"\n");
    
    

    printf("Enter Student Age: ");
    fflush(stdin);
    scanf("%d", &(st->Age));
    printf("\n");

    printf("Enter Student Gender: ");
    fflush(stdin);
    scanf("%d", &(st->Gender));
    printf("\n");
    
    // st->Classcode = (unsigned char*) malloc(12);

    printf("Enter Student Classcode: ");
    fflush(stdin);
    fgets(st->Classcode, 12 ,stdin);
    strtok(st->Classcode,"\n");
    printf("\n");
    

    printf("Enter Student Mark: ");
    fflush(stdin);
    scanf("%f", &(st->AverangeMark));


    

}

void Print(Student *st)
{
    printf("Student ID: %d\n", st->ID);
    printf("Student Name: %s\n", st->FullName);
    printf("Student Age: %d\n", st->Age);

    if (st->Gender == 0)
    {
        printf("Male\n");
    }else
    {
        printf("Female\n");
    }
    

    printf("Student Classcode: %s\n",st->Classcode);
    
    printf("Student Mark: %2f\n", st->AverangeMark);

}

/*********************************************************
                        Main
**********************************************************/

void main()
{   
    Student st1;
    unsigned char Name[25];
    st1.FullName = Name;
    unsigned char ClassCode[12];
    st1.Classcode = ClassCode;

    InputStudent(&st1);
    Print(&st1);


    // free(st1.FullName);
    // free(st1.Classcode);
    // free(st1);
}
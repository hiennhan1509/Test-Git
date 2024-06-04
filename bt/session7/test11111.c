#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char choice, view;
int n_student=0;
int i;
struct Student
{
    unsigned int ID;
    char fullname[24];
    float grade;
}s;

int Input()
{
    /*Enter ID*/
    printf("Enter ID: ");
    fflush(stdin);
    scanf("%d", &s.ID);


    /*Enter fullname*/
    printf("\nEnter your full name: ");
    fflush(stdin);
    gets(s.fullname);


    /*Enter Grade*/
    printf("\nEnter avergrade mark: ");
    fflush(stdin);
    scanf("%f", &s.grade);

}

void main()
{
    FILE *f;
    int a, ch;
    f=fopen("FILE 7.4.txt","wb");

    printf("Enter student information\n");

    Input();

    fprintf(f,"%d", s.ID);
    fputs(s.fullname,f);
    fprintf(f,"%.2f",s.grade);
    // do
    // {
    //    printf("Do you want to continue(Y/N): \n");
    //    scanf("%c",  &choice);
    //    switch(choice)
    //    {
    //     case 'y':
    //     case 'Y':
    //         {
    //             Input();
    //             fprintf(f,"%d", s.ID);
    //             fputs(s.fullname,f);
    //             fprintf(f,"%.2f",s.grade);
    //             n_student++;
    //         }
    //         break;
    //     case 'n':
    //     case 'N':
    //         {
    //             goto SHOW;
    //             break;
    //         }
    //     default: printf("Wrong choice!\n");
    //     break;
    //    }
    // }while(choice!='y'||choice!='Y');
    SHOW:
    fclose(f);
    f=fopen("D:\\Study for future\\Embedded system\\FPT CERTIFICATE\\SESSION 6-7\\FILE 7.4.txt","rb");
    struct Student s1[n_student];
    fread(&n_student, sizeof(s1), 1, f);
    printf("Do you want to view %d student information (Y/N)?\n", n_student+1);
    scanf("%c", &view);
    if(view=='Y'||view=='y')
    {
        for(i=0;i<n_student;i++)
        {
            fread(&s1[i], sizeof(s1), 1, f);
            printf("%-5d %-20s %-20f", s1[i].ID, s1[i].fullname, s1[i].grade);
        }
        printf("Complete\n");
    }
    else
    {
        exit(0);
        fclose(f);
    }
}
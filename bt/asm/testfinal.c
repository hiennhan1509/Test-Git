#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Staff_t
{
    char *name, address;
    int job;
    int level;
    long salary;
};

void InputStaff(struct Staff_t sInfor);
void Print(int nArr, struct Staff_t sInfor[]);

char g_ckey = 0;
unsigned short nStaff = 0;
unsigned short i = 0;
unsigned short j = 0;
unsigned short step = 0;

void main()
{   
    printf("Staff Managemet \n\n");
    printf("Enter How many staff: ");
    fflush(stdin);
    scanf("%d",&nStaff);

    struct Staff_t Staff[nStaff];

    do
    {
        printf("\nDo you want to enter information of staff (y/n): ");
        fflush(stdin);
        scanf("%c",&g_ckey);

        switch (g_ckey)
        {
        case 'y':
            {
                InputStaff(Staff[step]);
                step++;
            }
            break;

        case 'p':
        {   
            step = 0;
            printf("Name\t\t\t\tAdress\t\t\t\tJob\t\tLevel\t\tSarlary:\n");
            Print(nStaff, Staff);
            
        }
        break;
        case 'n':
            {
                exit(-1);
            }
            break;
        default:
            {
                printf("Invalid Option\n");
            }
            break;
        }
    } while ((g_ckey != 'n')||(step>=nStaff));
    


}

/*Input Staff*/
void InputStaff(struct Staff_t sInfor)
{
    sInfor.name = (char*) malloc(25);
    printf("\nEnter name of Staff: ");
    fflush(stdin);
    gets(sInfor.name);

    printf("\nEnter address of Staff: ");
    fflush(stdin);
    gets(&sInfor.address);

    do
    {
        printf("\nEnter job of Staff: ");
        fflush(stdin);
        scanf("%d", &sInfor.job);
    } while ((sInfor.job) < 1 || (sInfor.job) > 8); /*job is 1 to 8*/

    do
    {
        printf("\nEnter level of Staff: ");
        fflush(stdin);
        scanf("%d", &sInfor.level);
    } while ((sInfor.level) < 1 || (sInfor.level) > 7); /*level is 1 to 7*/

    do
    {
        printf("\nEnter salary of Staff: ");
        fflush(stdin);
        scanf("%d", &sInfor.salary);
    } while (sInfor.salary < 0);

    free(sInfor.name);
}

void Print(int nArr ,struct Staff_t sInfor[])
{   
    for(i = 0; i < nArr; i++ )
    {
        printf("%-24s %-24s %1d %1d %10d VND", sInfor[i].name, sInfor[i].address, sInfor[i].job, sInfor[i].level,sInfor[i].salary);
    }
}


/*sort name*/
void SortName(int nArr, struct Staff_t sInfor[])
{
    char status = 0;
    struct Staff_t tempstruct;

    for (i = 0; i < nArr - 1; i++)
    {
        for (j = i + 1; j < nArr; j++)
        {
            status = strcmp(sInfor[i].name, sInfor[j].name); /*I dont have enough time beacause i use strcmp*/
            if (status > 0)
            {
                tempstruct = sInfor[i];
                sInfor[i] = sInfor[j];
                sInfor[j] = tempstruct;
            }
        }
    }
}
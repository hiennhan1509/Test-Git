#include <stdio.h>
#include <string.h>

struct Staff_t
{
    char *name, address;
    int job;
    int level;
    long salary;
};

void InputStaff(struct Staff_t sInfor);
char g_ckey = 0;
unsigned short nStaff = 0;
unsigned short i = 0;

void main()
{   
    printf("Staff Managemet \n\n");
    printf("Enter How many staff: ");
    fflush(stdin);
    scanf("%d",&nStaff);
    printf("\nDo you want to enter information of staff (y/n): ");
    fflush(stdin);
    scanf("%d",&g_ckey);

    struct Staff_t Staff[nStaff];

    do
    {
        InputStaff(Staff[i]);
        i++;
    } while ((g_ckey != 'y')||(i>nStaff));
    
}

/*Input Staff*/
void InputStaff(struct Staff_t sInfor)
{
    printf("\nEnter name of Staff: ");
    fflush(stdin);
    gets(sInfor.name);
    getchar();

    printf("\nEnter address of Staff: ");
    fflush(stdin);
    gets(sInfor.name);
    getchar();

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
}

/*sort name*/
void SortName(int nArr, struct Staff_t sInfor[])
{
    char status = 0;
    struct tStudent tempstruct;

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
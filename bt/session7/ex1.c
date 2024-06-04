#include <stdio.h>
#include <string.h>

int i = 0;
char sFileName[64] = "../Ftext/testex1.txt";

void main()
{
    FILE *fp;
    char arr[64];
    int SizeString;

    fp = fopen(sFileName, "r");

    // for(i = 0; i<10 ; i++)
    // {
    //     fputs("write stament 10 times ", fp);
    //     fprintf(fp, "%s","write stament n times ");
    // }
    
    fflush(fp);
    memset(arr, 0 , sizeof(arr));

    fseek(fp, 17 , SEEK_SET);
    //SizeString = ftell(fp);

    //printf("%d ", SizeString);
    fgets(arr, 2 , fp);

    puts(arr);


    
    

}
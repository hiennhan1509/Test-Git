#include <stdio.h>

char str[50] = "  English is International   language";
int i = 0;
int n = 50;
int c;

/*delete space*/
void count()
{
    for(i = 0; i<n; i++)
    {
        if(str[0] == ' ')
        {
            str[i] == str[i+2];
        }
        
    }
    
    // for(i = 1; i<n; i++)
    // {
    //     if((str[i] == ' ')&&(str[i+1] == ' '))
    //     {
    //         str[i] = str[i+1];
    //     }
    // }
        printf("%s ", str);
}

void main()
{
    count();
}
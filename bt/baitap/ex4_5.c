#include <stdio.h>

char str[50] = "  English is International   language";
int i = 0;
int n = 50;
int c;

/*count word in sentences*/
void count()
{
    for(i = 0; i<n; i++)
    {
        if((str[i] == ' ')&&(str[i+1] != ' '))
        {
            c+=1;
        }
    }
    
    printf("%d ", c);
}

void main()
{
    count();
}
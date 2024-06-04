#include <stdio.h>
#include <string.h>

unsigned short f_CountWord(unsigned char arr[], unsigned char n);
void f_ClearSpace(unsigned char arr[], unsigned char n);
// count words
void main()
{
    unsigned char arr[] = "    English is the international language ";
    unsigned short count = strlen(arr);
    f_ClearSpace(arr,count);
    printf("%s \n%d",arr, strlen(arr));
    printf("\n%d", f_CountWord(arr, count));
}

unsigned short f_CountWord(unsigned char arr[], unsigned char n)
{
    unsigned short i = 0;
    unsigned wordcount = 1;
    // f_ClearSpace(arr, n);
    if (arr[0] == 0)
    {
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        if ((arr[i] != ' ') && (arr[i + 1] == ' '))
        {
            wordcount++;
        }

        if ((arr[i] == ' ') && (i == n - 1))
        {
            wordcount = 0;
        }

        if (i == n - 1)
        {
            if ((arr[i] == ' ') && (arr[i - 1] != ' '))
            {
                wordcount = 1;
            }
        }
    }
    return wordcount;
}

void f_ClearSpace(unsigned char arr[], unsigned char n)
{
    unsigned short j = 0;
    unsigned short i = 0;
    unsigned char countflag = 0;

    while (arr[i] == ' ')
    {
        countflag++;
        i++;
    }
    
    if (countflag != 0)
    {
        for (i = 0; i < n-countflag; i++)
        {
            arr[i] = arr[i+countflag];
        }
        arr[n-countflag] = 0;
        countflag = 0;
    }
    

    for (i = 0; i < n - 1; i++)
    {   
        while ((arr[i] == ' ') && (arr[i + 1] == ' '))
        {
            for (j = i + 1; j < n - 1; j++)
            {
                arr[j] = arr[j + 1];
                if (j == n - 2)
                {
                    arr[j+1] = 0;
                }
                
            }
        }

        if ((arr[i] == ' ')&&(arr[i+1] == 0) )
        {
            arr[i] = 0;
        }
        
    }
      
    
}

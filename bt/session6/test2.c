#include <stdio.h>
 
const int KICHCO = 3;
 
int main ()
{
   char  mang1[5] = "abcde";
   char  mang2[5] = "ghijk";

   int i, j;
   char **contro;
 
//    for ( i = 0; i < KICHCO; i++)
//    {
//       contro[i] = &mang[i]; /* gan dia chi cua so nguyen. */
//    }

    contro[0] = mang1;
    contro[1] = mang2;
    


    for (i = 0; i < 2; i++)
    {
        // for ( j = 0; j < 6; j++)
        // {
            printf("%s ", contro[i]);
        //}
        
    }
    
   
   return 0;
}
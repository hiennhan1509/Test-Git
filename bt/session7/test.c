#include <stdio.h>



int main ()
{
   FILE *fp;

   fp = fopen("baitapc.txt", "w+");

   fputs("Hoc c co ban va nang cao tai VietJack.", fp);
   fputs("Loat bai thu vien C chuan.", fp);

   fclose(fp);
   
   return(0);
}
#include <stdio.h>

    struct stdent
    {
        char *sID;
        char *FullName;
        unsigned short iAge;
        char *Gender;
        char *ClassID;  
        float fAverangeMark;
    };

void main()
{   
   
    struct stdent var;
    var.sID = "asjdai123";
    var.iAge = 23;
    printf("%s", var.sID);
    //printf(" %d", .sID);

    
}


#include <stdio.h>
#include <string.h>

#define FIRST_BYTE_TO_READ 10


int i = 0;
void EnterFileName(unsigned char sFileName[50])
{
    printf("\nEnter your file path: ");
    fgets(sFileName, 50, stdin);
    strtok(sFileName, "\n"); /*delete \n*/
}

int main()
{
    FILE *fp3 = NULL;
    unsigned int nSizeofFile = 0;
    char sFilename[64] = "abc.bin";
    unsigned char arr[10];
    // EnterFileName(sFilename);
    fp3 = fopen(sFilename, "rb");
    if (fp3 == NULL)
    {
        printf("\n cannot open file");
        return -1;
    }

    fseek(fp3, 0, SEEK_END);
    nSizeofFile = ftell(fp3);
    memset(arr, 0, sizeof(arr));
    fseek(fp3,0,SEEK_SET);
    fread(&arr[0], sizeof(char), 1, fp3);
    printf("%c", arr[0]);
    return 0;
}

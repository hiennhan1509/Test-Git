#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int idx;
    int len;
    char* buf;
}object_t;

object_t value;

object_t creat_object(int index, int length);

int main()
{
    value = creat_object(5,10);
    printf("%d",value.idx);
    printf("%d",value.len);
    printf("%s",value.buf);

    free(value.buf);
}

object_t creat_object(int index, int length)
{
    object_t obj;
    if(length > 0)
    {
        obj.idx = index;
        obj.len = length;
        obj.buf =  (char*)malloc(sizeof(char) * length);
        fgets(obj.buf,length * sizeof(char),stdin);
        if(obj.buf != NULL)
            return obj;
    }
    return obj;
}


#include <stdio.h>

typedef struct _MESSAGE_HEADER
{
    char head_byte;
    short message_id;
    unsigned int length;
} MESSAGE_HEADER, *MESSAGE_HEADER_PTR;

void main()
{
    // MESSAGE_HEADER value;
    // MESSAGE_HEADER *p;
    // value.head_byte = 10;
    // printf("%-p \n", value.head_byte);

    // p->head_byte = value.head_byte;
    // printf("%08X\n", p->head_byte);
}

void receive_data_complete(void *buffer) /* Buffer is received message data */
{

    MESSAGE_HEADER_PTR p_message_header;

    p_message_header = (MESSAGE_HEADER_PTR)buffer;
    /* Add code here */
}   
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeTemp
{
    int n1;
    float f2;
    struct NodeTemp *next;

} Node;

void Print(Node *p);
Node *addFirst(Node *head, Node *new, Node *curFirst);
Node *Insert(Node *Cur, Node *New, Node *Next);

void main()
{
    /*Initialize nodes*/
    Node *pHead = NULL;
    Node *pFirst = NULL;
    Node *pSecond = NULL;
    Node *pThird = NULL;
    Node *pTail = NULL;
    Node *pNewFirst = NULL;
    Node *pNewInsert = NULL;

    /*alocate memory*/
    pFirst = malloc(sizeof(Node));
    pSecond = malloc(sizeof(Node));
    pThird = malloc(sizeof(Node));
    pNewFirst = malloc(sizeof(Node));
    pNewInsert = malloc(sizeof(Node));

    /*Assign data*/
    pFirst->n1 = 1;
    pFirst->f2 = 2.0;
    pSecond->n1 = 3;
    pSecond->f2 = 4.0;
    pThird->n1 = 5;
    pThird->f2 = 6.7;
    pNewFirst->n1 = 99;
    pNewFirst->f2 = 88.8;
    pNewInsert->n1 = 101;
    pNewInsert->f2 = 102.3;

    /*Connect nodes*/
    pFirst->next = pSecond;
    pSecond->next = pThird;
    pThird->next = pTail;

    /*Save address of node 1st*/
    pHead = pFirst;

    /*add at first node use function*/
    pHead = addFirst(pHead, pNewFirst, pFirst);

    /*Insert node*/
    pThird = Insert(pSecond, pNewInsert, pThird);

    Print(pSecond);

    free(pFirst);
    free(pSecond);
    free(pThird);
    free(pNewFirst);
    free(pNewInsert);
}

/*Print linked list*/
void Print(Node *p)
{
    while (p != NULL)
    {
        printf("%d %.2f \n", p->n1, p->f2);
        p = p->next;
    }

    free(p);
}

/*add Node at first*/
Node *addFirst(Node *head, Node *new, Node *curFirst)
{
    head = new;
    new->next = curFirst;
    return head;
}

/*add Node*/
Node *Insert(Node *Cur, Node *New, Node *Next)
{
    Cur->next = New;
    New->next = Next;
    return Cur;
}
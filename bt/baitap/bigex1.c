#include <stdio.h>

unsigned int arr[100];
unsigned char i = 0;
unsigned char n = 5;
void nhap();
void switch_c();
void switch_p();
void switch_i();
void switch_d();
void switch_f();
void switch_g();
void switch_s();
void xuongdong();

char key;


void main()
{   
    do
    {   
        printf("CT quan ly day so\n");
        printf("nhap c hoac C de clear data cu va nhap day moi\n");
        printf("nhap p hoac P de in tat ca phan tu cua day\n");
        printf("nhap i hoac I de chen 1 phan tu vao vi tri k\n");
        printf("nhap d hoac D de xoa phan tu tai vi tri k\n");
        printf("nhap f hoac F de tim kiem 1 gia tri x co trong day hay khong\n");
        printf("nhap g hoac G de in ra so lon nhat\n");
        printf("nhap s hoac S de in ra so nho nhat\n");
        printf("nhap q hoac Q de thoat khoi chuong trinh\n");
        printf("nhap phim bat ki: ");
        fflush(stdin);      
        scanf("%c",&key);

    
        if ((key == 'p') || (key == 'P'))
        {
            switch_p();
        } else if ((key == 'i') || (key == 'I'))
        {
            switch_i();
        } else if ((key == 'd') || (key == 'D'))
        {
            switch_d();
        } else if ((key == 'f') || (key == 'F'))
        {
            switch_f();
        } else if ((key == 'g') || (key == 'G'))
        {
            switch_g();
        } else if ((key == 's') || (key == 'S'))
        {
            switch_s();
        }else
        {
            switch_c();
        }

    }while ((key != 'q') && (key != 'Q'));
} 

void nhap()
{    
    int k = 0;
    int flag = 0;

    for(i = 0; i < n; i++)
    {           
        do
        {   
            flag = 0;

            printf("nhap phan tu thu %d = ", i+1);
            scanf("%d",&arr[i]);

            for(k = 0; k < n; k++)
            {    
                if((arr[i] == arr[k])&&(i != k))
                {
                    flag = 1;
                }
            }
        }while((arr[i] < 1) || (arr [i] > 200) || (flag == 1));
               
    }
}

void switch_c()
{
    int k = 0;
    
    for(k = 0; k < n; k++) 
    {
        arr[k] = 0;
        i = 0;
    }

    nhap();
    xuongdong();
}        

void switch_p()
{   
    int k = 0;

    for(k = 0; k < n; k++)
    {  
        if((arr[k] > 0) && (arr [i] <= 200))
        {
            printf("%d ",arr[k]);
        }
        else
        {
            printf("day trong");
            break;
        }
    }
    xuongdong();
}

void switch_i()
{  
    int k = 0;
    int j = 0;
       
    printf("nhap vi tri muon chen thu k = ");
    scanf("%d", &k);
    
    if((k >= 0) && (k < n))
    {    
        for (j = n-2; j >= k; j--) /*n-2 de cho khong tran ra khoi mang*/
        {
            arr[j+1] = arr[j];
        }
        
        printf("nhap gia tri thu k = ");
        scanf("%d",&arr[k]);
    
        for (j = 0; j < n; j++)
        {
            printf("%d ",arr[j]);
        }
    }
    xuongdong();
}   

void switch_d()
{     
    int k = 0;
       
    printf("nhap vi tri muon xoa thu k = ");
    scanf("%d", &k);
    
    if((k >= 0) && (k < n))
    {    
        if((arr[k]>0)&&(arr[k])<200)
        {
            arr[k] = 0;
        }
        else
        {
            printf("khong co phan tu o vi tri k = %d", k + 1);
        }        
    }
    
    for(k = 0; k < n; k++)
    {
        printf("gia tri cua phan tu thu %d = %d \n" , k + 1, arr[k]);
    }

    xuongdong();
}

void switch_f()
{
    int k = 0;
    int x = 0;
    
    printf("nhap gia tri x muon tim kiem = ");
    scanf("%d", &x);

    if((x >= 0) && (x <= 200))
    {   
        for(k = 0; k < n; k++)
        {
            if(arr[k] == x)
            {
                printf("vi tri cua gia tri x trong day = %d ", k + 1);
                break;
            }
        }    
    }
    xuongdong();
}

void switch_g()
{
    int k = 0;
    int max = arr[0];

    for(k = 0; k < n; k++)
    {
        if(max < arr[k])
        {
            max = arr[k];
        }
    }
    printf("so lon nhat trong day = %d ", max);
    xuongdong();
}

void switch_s()
{
    int k = 0;
    int min = arr[0];

    for(k = 0; k < n; k++)
    {
        if(min > arr[k])
        {
            min = arr[k];
        }
    }
    printf("so nho nhat trong day = %d", min);
    xuongdong();    
}

void xuongdong()
{
    printf("\n\n\n\n\n");
}
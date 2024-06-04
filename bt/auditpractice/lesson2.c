#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

/*********************************************************
                    Decleration
**********************************************************/

typedef struct
{
    unsigned short ID;
    unsigned char *FullName;
    unsigned char Age;
    unsigned char Gender;
    unsigned char *Classcode;
    float AverangeMark;

} Student;

void Fibonaccy();
void goto_Fib();
void BCNN(int a, int b);
void UCLN(int a, int b);
void SoChinhPhuong(unsigned int a, unsigned int b);
void Getnumberofdecimal(unsigned int a, int *arr, int count);
int songuyentoXuoiNguoc(unsigned int a);
int Countnumberofdigit(unsigned int a);
void SoEmirp(int a);

/*********************************************************
                    Input Function
**********************************************************/
void InputStudent(Student *st)
{
    st->FullName = (char*) malloc(26);
    st->Classcode = (char*) malloc(20);
     
    
    printf("Enter Student ID: ");
    fflush(stdin);
    scanf("%d", &(st->ID));
    getchar();
    printf("\n");

    // st->FullName = (unsigned char*) malloc(26);

    printf("Enter Student Name: ");
    fflush(stdin);
    fgets(st->FullName, 26, stdin);
    strtok(st->FullName, "\n");

    printf("Enter Student Age: ");
    fflush(stdin);
    scanf("%d", &(st->Age));
    getchar();
    printf("\n");

    printf("Enter Student Gender: ");
    fflush(stdin);
    scanf("%d", &(st->Gender));
    getchar();
    printf("\n");

    // st->Classcode = (unsigned char*) malloc(12);

    printf("Enter Student Classcode: ");
    fflush(stdin);
    fgets(st->Classcode, 12, stdin);
    strtok(st->Classcode, "\n");
    printf("\n");

    printf("Enter Student Mark: ");
    fflush(stdin);
    scanf("%f", &(st->AverangeMark));
    getchar();
}

/*********************************************************
                    Printf Function
**********************************************************/
void Print(Student *st)
{
    printf("Student ID: %d\n", (st->ID));
    printf("Student Name: %s\n", (st->FullName));
    printf("Student Age: %d\n", (st->Age));

    if (st->Gender == 0)
    {
        printf("Male\n");
    }
    else
    {
        printf("Female\n");
    }

    printf("Student Classcode: %s\n", (st->Classcode));

    printf("Student Mark: %2f\n", (st->AverangeMark));
}

/*********************************************************
                        Main
**********************************************************/

/*********************************************************
                    Fibonaccy
**********************************************************/

void Fibonaccy()
{
    unsigned int i;
    unsigned int n[8];
    n[0] = 1;
    n[1] = 1;
    for (i = 2; i < 8; i++)
    {
        n[i] = n[i - 1] + n[i - 2];
    }
    for (i = 0; i < 8; i++)
    {
        printf("%d ", n[i]);
    }
}

void goto_Fib()
{
    unsigned int i = 2;
    unsigned int n[8];
    n[0] = 1;
    n[1] = 1;
    printf("%d %d ", n[0], n[1]);

LABEL:
    n[i] = n[i - 1] + n[i - 2];
    printf("%d ", n[i]);
    i++;
    if (i < 8)
    {
        goto LABEL;
    }

    // for ( i = 0; i < 8; i++)
    // {
    //     printf("%d ", n[i]);
    // }
}

/*********************************************************
                        BCNN
**********************************************************/
void BCNN(int a, int b)
{
    unsigned int i = 0;
    for (i = 1; i <= a * b; i++)
    {
        if ((i % a == 0) && (i % b == 0))
        {
            printf("BCNN = %d", i);
            break;
        }
    }
}

/*********************************************************
                        UCLN
**********************************************************/

void UCLN(int a, int b)
{
    unsigned int i = 0;
    unsigned temp;

    if (a > b)
    {
        for (i = b; i > 2; i--)
        {
            if ((a % i == 0) && (b % i == 0))
            {
                printf("UCLN = %d", i);
                break;
            }
            else
            {
                printf("UCLN = %d", 1);
            }
        }
    }
    else
    {
        for (i = a; i > 2; i--)
        {
            if ((a % i == 0) && (b % i == 0))
            {
                printf("UCLN = %d", i);
                break;
            }
            else
            {
                printf("UCLN = %d", 1);
            }
        }
    }
}

/*********************************************************
                    So chinh phuong
**********************************************************/
void SoChinhPhuong(unsigned int a, unsigned int b)
{
    if (a * a == b)
    {
        printf("b la so chinh phuong cua a");
    }
    else
    {
        printf("b khong la so chinh phuong cua a");
    }
}

/*********************************************************
                    So nguyen to
**********************************************************/
unsigned char Songuyento(unsigned int a)
{
    unsigned char flag = 0;
    if (a == 1)
    {
        printf("%d la so nguyen to\n", 1);
    }
    if (a > 1)
    {
        for (int i = 2; i <= a / 2; i++)
        {
            if (a % i == 0)
            {
                flag = 1; /*khong phai so nguyen to*/
                break;
            }
        }
        if (flag == 0)
        {
            printf("%d la so nguyen to\n", a);
        }
        else
        {
            printf("%d khong phai so nguyen to\n", a);
        }
    }
    if (a <= 0)
    {
        printf("%d khong la so nguyen to\n", a);
    }
    return flag; // flag = 0 la so nguyen to, flag = 1 khong phai so nguyen to
}

/*********************************************************
                So nguyen to xuoi nguoc
**********************************************************/
int songuyentoXuoiNguoc(unsigned int a)
{
    unsigned int flag = 0;

    if (a <= 0)
    {
        printf("a khong phai so nguyen to");
        return -1;
    }

    if (Songuyento(a) == 0)
    {
        unsigned int i = 0;
        unsigned int temp = a;
        unsigned int count = 0;
        count = Countnumberofdigit(a);

        unsigned int arr[count];
        unsigned char j = count - 1;
        if (a == 11)
        {
            printf("a la so nguyen to xuoi nguoc\n");
            return 0;
        }

        if (count % 2 == 0)
        {
            printf("a khong la so nguyen to xuoi nguoc\n");
        }
        else
        {
            unsigned k = count - 1;
            unsigned int temp1 = a;
            Getnumberofdecimal(a, arr, count);
            for (i = 0; i < count / 2; i++)
            {
                if (arr[i] != arr[count - 1 - i])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                printf("a khong la so nguyen to xuoi nguoc\n");
            }
            else
            {
                printf("a la so nguyen to xuoi nguoc\n");
            }
        }
    }
}

/*********************************************************
                        So Emirp
**********************************************************/

void SoEmirp(int a)
{
    int count = 0;
    int i = 0;
    unsigned int *ptr;
    unsigned int b = 0;
    if (Songuyento(a) == 0)
    {
        count = Countnumberofdigit(a);
        ptr = (unsigned int *)malloc(count * 4);
        Getnumberofdecimal(a, ptr, count);
        for (i = 0; i < count; i++)
        {
            b += ptr[i] * pow(10, count - i - 1);
        }

        if (Songuyento(b) == 0)
        {
            printf("%d %d la so Emirp", a, b);
        }
        else
        {
            printf("%d khong la so Emirp", a);
        }
    }
    else
    {
        printf("%d khong la so Emirp", a);
    }

    free(ptr);
}

/*********************************************************
                    Getnumberofdecimal
**********************************************************/
void Getnumberofdecimal(unsigned int a, int *arr, int count)
{
    unsigned int temp1 = a;
    unsigned int i = 0;
    for (i = 0; i < count; i++)
    {
        arr[i] = temp1 % 10;
        temp1 = temp1 / 10;
    }
}

/*********************************************************
                    Countnumberofdigit
**********************************************************/
int Countnumberofdigit(unsigned int a)
{
    unsigned int temp = a;
    int count = 0;
    do
    {
        temp = temp / 10;
        count++;
    } while (temp > 0);
    return count;
}

/*********************************************************
                    So Hoan Hao
**********************************************************/
int SoHoanHao(int a)
{
    int sum = 0;
    int i = 0;
    if (a <= 0)
    {
        printf("a khong phai la so hoan hao");
        return 0;
    }

    for (i = 1; i < a; i++)
    {
        if (a % i == 0)
        {
            sum += i;
        }
    }
    if (sum == a)
    {
        printf("a la so hoan hao");
    }
    else
    {
        printf("a khong phai la so hoan hao");
    }
    return 1;
}

/*********************************************************
                    So Ky Quac
**********************************************************/
int SoKiQuac(int a)
{
    int sum = 0;
    int i = 0;
    unsigned int flag = 0;
    if (a <= 1)
    {
        printf("a khong phai la so ky quac");
        return 0;
    }

    if (a == 2)
    {
        printf("a = %d la so ky quac",a);
        return 1;
    }
    

    for (i = 1; i <= a/2; i++) /*tim cac uoc chung*/
    {
        if (a % i == 0)
        {
            sum += i;
            if (sum == a)
            {
                printf("a khong phai so ky quac");
                return - 1;
            }
            else
            {
                flag = 1;
            }
        }
    }

    if ((flag == 1)&&(sum > a))
    {
        printf("a = %d la so ky quac",a);
    }else
    {
        printf("a = %d khong phai so ky quac",a);
    }
    return 1;
}

/*********************************************************
                    So Manh me
**********************************************************/
int SoManhMe(int a)
{
    unsigned int i = 0;

    if (a <= 0)
    {
        printf("a khong phai so manh me");
        return -1;
    }

    if (a == 1)
    {
        printf("a la so manh me");
        return 0;
    }

    unsigned char flag = 0;
    for (i = 2; i <= a / 2; i++)
    {
        if (a % i == 0)
        {
            if ((Songuyento(i) == 0) && (a % (i * i) == 0))
            {
                flag = 1;
                break;
            }
        }
        else
        {
            flag = 0;
        }
    }
    if (flag == 1)
    {
        printf("a = %d la so manh me", a);
    }
    else
    {
        printf("a = %d khong phai so manh me", a);
    }

    return 0;
}


/*********************************************************
                    So Bat kha xam pham (chưa xong)
**********************************************************/

int SoBatKhaXamPham(int a)
{   
    int i = 3;
    int j = 1;
    int sum = 0;

    if (a <= 2)
    {
        printf("a khong phai la so bat kha xam pham");
        return 0;
    }


    do /*tim cac uoc chung*/
    {
        sum = 0;
        for ( j = 1; j <= i/2 ; j++)
        {
            if (i % j == 0)
            {   
                sum += j;
            }
        }
        i++;
    }while(sum<=a);

    printf("sum = %d\n", sum);
    if (sum == a)
    {
        printf("a = %d khong phai so bat kha xam pham", a);
    }else
    {
        printf("a = %d la so bat kha xam pham", a);
    }
    
}







/*********************************************************
                        Main
**********************************************************/

void main()
{
    // Fibonaccy();
    // goto_Fib();
    // BCNN(20,4);
    // UCLN(20, 5);
    // SoChinhPhuong(3,25);
    // Songuyento(2);
    // songuyentoXuoiNguoc(0);
    // SoEmirp(73);
    // SoHoanHao(28);
    // SoManhMe(169);
    // SoKiQuac(836);
    // SoBatKhaXamPham(9);


    Student st1;
    InputStudent(&st1);
    Print(&st1);


    free(st1.FullName);
    free(st1.Classcode);
    
    
}
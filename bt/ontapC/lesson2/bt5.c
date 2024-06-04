#include <stdio.h>

enum consumption_Fee_per_level
{
    A = 600,
    B = 900,
    C = 1200,
    D = 1500
};
unsigned int f_Calculate_Electric_Consumption_fee(unsigned short ConsumptionNuber);
void f_fibonaccy(int value[], short count);
unsigned int f_UCLN(unsigned int a, unsigned int b);
unsigned int f_BCNN(unsigned int a, unsigned int b);

int main()
{
    short count = 10;
    int fibonancy_value[count];
    f_fibonaccy(fibonancy_value, count);
    printf("Fibonancy\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d\n", fibonancy_value[i]);
    }

    ////////////////////////////////////////
    printf("Consumption Fee\n");
    int consumption_fee = 0;
    consumption_fee = f_Calculate_Electric_Consumption_fee(10);
    printf("%d\n", consumption_fee);

    consumption_fee = f_Calculate_Electric_Consumption_fee(150);
    printf("%d\n", consumption_fee);

    consumption_fee = f_Calculate_Electric_Consumption_fee(151);
    printf("%d\n", consumption_fee);

    consumption_fee = f_Calculate_Electric_Consumption_fee(251);
    printf("%d\n", consumption_fee);

    printf("UCLN\n");
    unsigned int UCLN_value = 0;
    UCLN_value = f_UCLN(1000, 105);
    printf("%d\n", UCLN_value);

    printf("BCNN\n");
    unsigned int BCNN_value = 0;
    UCLN_value = f_BCNN(4,6);
    printf("%d\n", UCLN_value);
}

void f_fibonaccy(int value[], short count)
{
    unsigned short i = 0;
    value[0] = 1;
    value[1] = 1;
    for (i = 2; i < count; i++)
    {
        value[i] = value[i - 1] + value[i - 2];
    }
}

unsigned int f_Calculate_Electric_Consumption_fee(unsigned short ConsumptionNuber)
{
    unsigned int fee = 0;
    if (ConsumptionNuber <= 100)
    {
        fee = ConsumptionNuber * A;
    }

    if (ConsumptionNuber >= 101 && ConsumptionNuber <= 150)
    {
        fee = 100 * A + (ConsumptionNuber - 100) * B;
    }

    if (ConsumptionNuber >= 151 && ConsumptionNuber <= 250)
    {
        fee = 100 * A + 50 * B + (ConsumptionNuber - 150) * C;
    }

    if (ConsumptionNuber > 250)
    {
        fee = 100 * A + 50 * B + 100 * C + (ConsumptionNuber - 250) * D;
    }

    return fee;
}

unsigned int f_UCLN(unsigned int a, unsigned int b)
{
    unsigned int i = 1;
    if (a > b)
    {
        for (i = b; i >= 1; i--)
        {
            if ((a % i == 0) && (b % i == 0))
            {
                return i;
            }
        }
    }
    if (a < b)
    {
        for (i = a; i >= 1; i--)
        {
            if ((a % i == 0) && (b % i == 0))
            {
                return i;
            }
        }
    }
}

unsigned int f_BCNN(unsigned int a, unsigned int b)
{
    unsigned int i = 1;
    for (i = 2; i <= a * b; i++)
    {
        if ((i % a == 0) & (i % b == 0))
        {
            return i;
        }
    }
}

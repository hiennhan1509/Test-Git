#include <stdio.h>
#include <math.h>

void TriAngle(float a, float b, float c)
{
    float fPerimeter;
    float fArea;

    fPerimeter = (a + b + c)/2;
    fArea = sqrt(fPerimeter * (fPerimeter - a) * (fPerimeter - b) * (fPerimeter - c));
    printf ("%8.2f %8.2f", fPerimeter *2, fArea); 

}

void main ()
{
    TriAngle(3, 4, 5);
}
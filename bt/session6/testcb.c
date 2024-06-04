#include <stdio.h>

// void TargetFunc1(int a, float b)
// {
//     printf("\nThis is the callback function #1");
// }

// void TargetFunc2(int a, float b)
// {
//     printf("\nThis is the callback function #2");
// }

// typedef void (*Callback)(int a, float b); /* Same prototype with TargetFunc1 and TargetFunc2 */

// void RunCallback(Callback fp, int a, float b)
// {
//     (*fp)(a, b);
// }

// void main()
// {
//     Callback fp = &TargetFunc2; /* fp points to a target function */
//     RunCallback(fp, 10, 3.14); /* start callback */
// }


void A(){ 
  printf("I am function A\n");
}
 
// callback function
void B(void (*ptr)())
{
    (*ptr)(); // callback to A
}
 
int main()
{
    void (*ptr)() = A;
 
    // calling function B and passing
    // address of the function A as argument
    B(ptr);
 
    return 0;
}
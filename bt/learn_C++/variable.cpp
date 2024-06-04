#include <iostream>
using namespace std;

class Employee
{
private:
    // Private attribute
    int salary;

public:
    // Setter
    void setSalary(int s)
    {
        salary = s;
    }
    // Getter
    int getSalary()
    {
        return salary;
    }
};

class complex
{
private:
    float r, i;

public:
    complex(float r, float i)
    {
        this->r = r;
        this->i = i;
    }
    complex() {}
    void displaydata()
    {
        cout <<"real part = "<< r << endl;
        cout <<"imaginary part = "<< i << endl;
    }
    complex operator+(complex c)
    {
        return complex(r + c.r, i + c.i);
    }
};
int main()
{
    // complex a(2, 3);
    // complex b(3, 4);
    // complex c = a + b;
    // c.displaydata();
    // string str1;
    // getline(cin,str1);
    cout << sizeof('A');
    return 0;
}

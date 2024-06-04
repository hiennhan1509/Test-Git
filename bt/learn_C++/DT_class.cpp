#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

class DT
{
private:
    int n;
    double *a;
public:
    DT operator+(const DT &d2); // + 2 da thuc
    DT operator-(DT d); // doi dau da thuc
    DT operator*(const DT &d2); // nhan 2 da thuc
    double operator^(const double &x); // thay so vao tinh ket qua
    friend istream& operator>>(istream& is, DT &d);
    friend ostream& operator<<(ostream& os, const DT &d);    
};

    istream& operator>>(istream& is, DT &d)
    {
        cout << ("Bac da thuc: ");
        cin >> d.n;
        d.a = new double[d.n + 1];
        cout << "\nNhap cac he so cua da thuc: ";
        for (int i = 0; i <= d.n; i++)
        {
        is >> d.a[i];
        }
        return is;
    }

    ostream& operator<< (ostream& os, const DT &d)
    {
        os << "\nCac he so: ";
        for (int i = 0; i <= d.n; i++)
        {
            os << d.a[i]<<" ";
        }
        return os;
    }


DT DT::operator+(const DT &d2)
{
    DT result;
    int k,i;
    k = n > d2.n ? this->n : d2.n;
    result.a = new double[k+1];
    for ( i = 0; i <= k; i++)
    {
        result.a[i] = 0;
    }
    
    for (i = 0; i <= k; i++)
    {
        if ((i<=n)&&(i<=d2.n))
        {
            result.a[i] = a[i] + d2.a[i];
        }else if (i<=n)
        {
            result.a[i] = a[i];
        }
        else result.a[i] = d2.a[i];
    }
    i = k;
    while (i>0 && result.a[i] == 0) --i;
    result.n = i;
    return result;
}

DT DT::operator-(DT d)
{
    for (int i = 0; i <= d.n; i++)
    {
        d.a[i] = -d.a[i];
    }
    return d;   
}

DT DT::operator*(const DT &d2)
{
    DT d;
    int i,j,k;
    k = d.n = this->n + d2.n;
    d.a = new double[k + 1];
    for (i = 0; i <= k; i++) d.a[i] = 0;
    for ( i = 0; i <= this->n; i++)
    for ( j = 0; j <= d2.n; j++)
    d.a[i+j] += this->a[i] * d2.a[j];
    return d;
}

double DT::operator^(const double &x)
{
    double result = 0, t = 1.0;
    for (int i = 0; i <= this->n; i++)
    {
        result += this->a[i] * t;
        t*=x;
    }
    return result;   
}

int main(void)
{
    DT u,v,r;
    cin>>u;
    cin>>v;
    r = u+v;
    cout << r;
}


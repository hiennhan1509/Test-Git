#include <iostream>
#include <math.h>
#include <conio.h>
#include <fstream>
using namespace std;

typedef struct
{
    double hs[20]; // mang chua cac he so cua da thuc
    unsigned short n; // bac cua da thuc
}Dathuc;

ostream& operator<< (ostream &os, Dathuc d);
istream& operator>> (istream &is, Dathuc &d);

Dathuc operator- (const Dathuc &d);
Dathuc operator+ (Dathuc d1, Dathuc d2);
Dathuc operator- (Dathuc d1, Dathuc d2);
Dathuc operator* (Dathuc d1, Dathuc d2);
double operator^ (Dathuc d, double x);

ostream& operator<< (ostream &os, Dathuc d)
{
    os <<"Cac he so (tu bac cao -> thap): ";
    for (int i = d.n; i >= 0; i--)
        os<< d.hs[i]<<" "; 
    return os;
}

istream& operator>> (istream &is, Dathuc &d)
{
    cout << "\nNhap bac cua da thuc: ";
    cin >> d.n;
    for (int i = d.n; i >= 0; i--)
    {
        cout << "\nHe so bac " << i << " = ";
        is >> d.hs[i];
    }
    return is;
}

Dathuc operator- (const Dathuc &d)
{
    Dathuc a;
    for (int i = d.n; i >= 0; i--)
        a.hs[i] = -d.hs[i];
    a.n = d.n;
    return a;
}

Dathuc operator+ (Dathuc d1, Dathuc d2)
{   
    Dathuc s;
    short k, i;
    k = d1.n >= d2.n ? d1.n : d2.n;
    for (i = k; i >= 0; i--)
    {
        if (i<= d1.n && i <= d2.n)
            s.hs[i] = d1.hs[i] + d2.hs[i];
        else if (i <= d1.n)
            s.hs[i] = d1.hs[i];
        else 
            s.hs[i] = d2.hs[i];
    }
    
    i = k;
    while (i>0 && s.hs[i] == 0) i--;
    s.n = i;
    return s;
}

Dathuc operator- (Dathuc d1, Dathuc d2)
{
    Dathuc sub;
    sub = d1 + (-d2);
    return sub;
}

Dathuc operator* (Dathuc d1, Dathuc d2)
{
    Dathuc mul;
    int i, j, k;
    k = mul.n = d1.n + d2.n;
    for ( i = k; i >= 0; i--) mul.hs[i] = 0;
    for ( i = d1.n; i >= 0; i--)
        for (j = d2.n; j >= 0; j--)        
            mul.hs[i+j] += d1.hs[i] * d2.hs[j];
    return mul;
}

double operator^ (Dathuc d, double x)
{
    double result = 0;
    double t = 1.0;
    for (int i = 0; i <= d.n; i++)
    {
        result += d.hs[i] * t;
        t *= x;
    }
    return result;
}

int main(void)
{
    Dathuc s,p,q,r,t;
    cout << "\nNhap bieu thuc p: ";
    cin >> p;
    cout << "\nNhap bieu thuc q: ";
    cin >> q;
    cout << "\nNhap bieu thuc r: ";
    cin >> r;
    cout << "\nNhap bieu thuc t: ";
    cin >> t;

    s = -(p+q) * (r - t);
    // g = s^3;
    cout << "\nHe so cua s: "<< s;
    return 0;
}

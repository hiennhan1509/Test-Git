/* chồng toán tử cho phân số (cộng trừ nhân chia) */

#include <conio.h>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

typedef struct
{
    int tu,mau;
}PS;

ostream& operator<< (ostream& os, PS p);
istream& operator>> (istream& is, PS &p);
int ucln (int x, int y);
PS rutgon(PS p);
PS operator+ (PS p1, PS p2);
PS operator- (PS p1, PS p2);
PS operator* (PS p1, PS p2);
PS operator/ (PS p1, PS p2);

ostream& operator<< (ostream& os, PS p)
{
    os<<p.tu<< '/' << p.mau;
    return os;
}

istream &operator>> (istream& is, PS &p)
{
    cout << "Nhap tu va mau: \n";
    is>>p.tu>> p.mau; 
    return is;
}
int ucln (int x, int y)
{
    x = abs(x); y = abs(y);
    if (x*y == 0) return 1;
        while (x!=y)
            if (x>y) x -= y;
            else y -= x;
    return x;
}

PS rutgon(PS p)
{
    PS q;
    int x;
    x = ucln(p.tu,p.mau);
    q.tu = p.tu/x;
    q.mau = p.mau/x;
    return q; 
}

PS operator+ (PS p1, PS p2)
{
    PS q;
    q.tu = p1.tu * p2.mau + p2.tu * p1.mau;
    q.mau = p1.mau * p2.mau;
    return rutgon(q);
}

PS operator- (PS p1, PS p2)
{
    PS q;
    q.tu = p1.tu * p2.mau - p2.tu * p1.mau;
    q.mau = p1.mau * p2.mau;
    return rutgon(q);
}

PS operator* (PS p1, PS p2)
{
    PS q;
    q.tu = p1.tu * p2.tu;
    q.mau = p1.mau * p2.mau;
    return rutgon(q);
}

PS operator/ (PS p1, PS p2)
{
    PS q;
    q.tu = p1.tu * p2.mau;
    q.mau = p1.mau * p2.tu;
    return rutgon(q);
}

int main(void)
{
    PS p, q;
    PS s;
    cout << "\nNhap PS p,q: \n";
    cin >> p,q;
    s = p * q;
    cout << "\nPhan so s = " << s;
    return 0;
}

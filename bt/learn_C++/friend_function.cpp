/********************************************************************************************
    // 2 lớp VT (vecto), MT (ma trận)
    // 3 hàm:
    + Hàm bạn với VT để in 1 vectơ: friend void in(const VT &x);
    + Hàm bạn với MT để in 1 ma trận: friend void in(const MT &a);
    + Hàm bạn với cả 2 lớp MT và VT dùng để nhân ma trận với vec tơ: 
    friend VT tich (const MT &a, const VT &x);
    nội dung: nhập 1 ma trận vuông cấp n, và  vector cấp n sau đó thực hiện nhân ma trận vs vecto
*********************************************************************************************/

#include <conio.h>
#include <iostream>
#include <math.h>

using namespace std;

class VT;
class MT;

class VT
{
private:
    int n;
    double vtr[20];
public:
    void nhapVT()
    {
        cout << "\nNhap so phan tu cua vector: ";
        cin >> n;
        cout << "\nNhap vector: ";
        for (int k = 0; k < n; k++)
        {
            cin >> vtr[k];
        }
    }

    friend void in(const VT &x)
    {
        cout << "\nVector V = ";
        for (int k = 0; k < x.n; k++)
        {
            cout << x.vtr[k] << " ";
        }
    }

    friend VT tich(const MT &a, const VT &x);
};

class MT
{
private:
    int n;
    double mtrx[20][20];
public:
    void nhapMT()
    {
        cout << "\nNhap cap cua ma tran n = ";
        cin >> n;
        cout << "\nNhap MT vuong cap n: ";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << "\nNhap phan tu: ";
                cin >> mtrx[i][j];
            }
        }
    }

    friend void in(const MT &a)
    {
        cout << "\nMa tran A = \n";
        for (int i = 0; i < a.n; i++)
        {
            for (int j = 0; j < a.n; j++)
            {
                cout << a.mtrx[i][j] << " ";
            }
            cout << endl;
        }
    }

    friend VT tich(const MT &a, const VT &x);

};

VT tich(const MT &a, const VT &x)
{
    VT result;
    result.n = a.n;
    result.vtr[0] = 0;
    for (int i = 0; i < a.n; i++)
    {
        for ( int j = 0; j < x.n; j++)
        {
            result.vtr[i] += x.vtr[i]*a.mtrx[i][j];
        }
    }
    return result;
}


int main()
{
    MT mt1;
    VT vt1, vt2;

    vt1.nhapVT();

    mt1.nhapMT();

    vt2 = tich(mt1,vt1);
    in(vt2);
    return 0;
}

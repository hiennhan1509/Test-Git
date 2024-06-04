/*yêu cầu: nhập 1 dãy hcn sau đó tìm hcn có max diện tích và hcn có max chu vi
1. lớp HINH_CN
    + thuộc tính: d và r (chiều dài và rộng)
    + các phương thức: 
        void nhapsl();
        int dientich();
        int chu_vi();
2. Lớp DAY_HINH_CN
    + thuộc tính : int n; HINH_CN *h; 
    + Các phương thức:
    void nhapsl();
    HINH_CN hinh_dt_max();
    HINH_CN *hinh_cv_max();
*/

#include <conio.h>
#include <iostream>

using namespace std;

class HINH_CN
{
private:
    double d,r;
public:
    void nhapsl();
    void in_kichthuoc();
    double dientich();
    double chu_vi();
};

void HINH_CN::nhapsl()
{
    cout << "\nNhap chieu dai va chieu rong: ";
    cin >> d >> r;
}

void HINH_CN::in_kichthuoc()
{
    cout << "\nChieu dai d = " << d;
    cout << "\nChieu rong r = " << r;
}

double HINH_CN::dientich()
{
    return d * r;
}

double HINH_CN::chu_vi()
{
    return ((d + r) * 2);
}

class DAY_HINH_CN
{
private:
    int n;
    HINH_CN *h;
public:
    void nhapsl();
    HINH_CN hinh_dt_max();
    HINH_CN *hinh_cv_max();
};

void DAY_HINH_CN::nhapsl()
{
    cout << "\nNhap so luong HCN: ";
    cin >> n;
    h = new HINH_CN[n+1];
    for (int i = 0; i < n; i++)
    {
        cout <<"\nHinh thu " << i + 1;
        h[i].nhapsl();
    }
}

HINH_CN DAY_HINH_CN::hinh_dt_max()
{
    int index_temp = 0;
    for (int i = 1; i < n; i++)
    {
        if (h[index_temp].dientich() < h[i].dientich() )
        {
            index_temp = i;
        }
    }
    return h[index_temp];
}

HINH_CN *DAY_HINH_CN::hinh_cv_max()
{
    int index_temp = 0;
    for (int i = 1; i < n; i++)
    {
        if (h[index_temp].chu_vi() < h[i].chu_vi() )
        {
            index_temp = i;
        }
    }
    return (h+index_temp);
}



int main(void)
{
    DAY_HINH_CN d;
    HINH_CN hinh_dtmax;
    d.nhapsl();
    hinh_dtmax = d.hinh_dt_max();
    cout << "\nHinh co dt max co kich thuoc: \n";
    hinh_dtmax.in_kichthuoc();
    HINH_CN *hinh_cvmax;
    hinh_cvmax = d.hinh_cv_max();
    cout << "\nHinh co cv max co kich thuoc: \n";
    hinh_cvmax->in_kichthuoc();
    getch();
}


#include <iostream>

using namespace std;

class PhuongTienGiaoThong
{
	protected:
		string HangSX,TenPT;
		int NamSX;
		float VantocMax;
	public:
		void Nhap();
		void Xuat();	 	
};

class Oto : public PhuongTienGiaoThong
{
	private:
		int SLghe;
		string KieuDC;
		float VTCS;
	public:
		float vantoccoso(Oto oto1);
		void Nhap();
		void Xuat();
};

float Oto::vantoccoso(Oto oto1)
{
	VTCS = oto1.VantocMax / 4 ;	
	return VTCS;
}

void PhuongTienGiaoThong::Nhap()
{
	cout << "Hang SX: ";getline(cin,HangSX);
	cout << "Ten PT: ";getline(cin,TenPT);
	cout << "Nam SX: ";cin >> NamSX;
	cout << "Van Toc Max: ";cin >> VantocMax;
}

void PhuongTienGiaoThong::Xuat()
{
	cout << "Hang SX: "<< HangSX <<endl;
	cout << "Ten PT: " << TenPT << endl;
	cout << "Nam SX: " << NamSX << endl;
	cout << "Van Toc Max: " << VantocMax << "Km/h" << endl;
}

void Oto::Nhap()
{
	PhuongTienGiaoThong::Nhap();
	cout << "So cho ngoi: "; cin >> SLghe;
	cout << "Kieu DC: ";cin >> KieuDC;
}

void Oto::Xuat()
{
	PhuongTienGiaoThong::Xuat();
	cout << "So cho ngoi: " << SLghe << endl;
	cout << "Kieu DC: " << KieuDC << endl;
}


int main()
{
	PhuongTienGiaoThong PTGT;
	int chon,i,n;
	float Vtcs;
	cout <<"Chon phuong thuc nhap: " << endl;
	cout <<"1. 1 xe " << endl;
	cout <<"2. Nhieu xe" << endl;
	cin >> chon;
	
	
	switch(chon)
	{
		case 1:
			{
				PTGT.Nhap();
				cout << endl;
				PTGT.Xuat();
			}
			break;
		case 2:
			{
				int n ;
				cout << "So luong xe muon nhap: ";
				cin >> n;
				cin.ignore();
				
				Oto oto[n];
				
				for(i = 0; i < n;i++)
				{
					int dem = i+1;
					cout <<"Xe so "<< dem << ":" << endl;
					oto[i].Nhap();
					cin.ignore();
					cout << endl;
					
					
					
				}
				
				
				for(i = 0; i < n;i++)
				{
					oto[i].Xuat();
					cout << endl;
				}
				
			}
			break;
		default:
			break;
	}
	
}
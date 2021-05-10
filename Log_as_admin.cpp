#include"Log_as_ad.h"
#include"LOGIN.h"
void check_acc_ad(string usr, string psw)
{
	if (psw[0] == 'A' && psw[1] == 'D')
	{
		ifstream f;
		f.open("acc_ad.csv");
		string acc = account(usr, psw);
		int c = 0;
		int n = count_acc_in_csv("acc_ad");
		while (!f.eof())
		{
			c++;
			string acc1;
			f >> acc1;
			if (acc.compare(acc1) != 0)
			{
				if (c < n)
				{
					continue;
				}
				else if (c == n)
				{
					cout << "\t\tWrong password or username !!!" << endl;
					cout << "Press Enter to return menu main !!!" << endl;
					cin.ignore();
					//Nhan phim 0 de quay ve menu chinh
				}
			}
			else
			{
				cout << "\t\tLogin sucessed !!!" << endl;
				break;
			}
		}
		f.close();
	}
	else
	{
		cout << "\t\tWrong password or username !!!" << endl;
		cout << "\t\tPress Enter to return -Main Menu- !!!" << endl;
		cin.ignore();
	}
}
void login_as_admin(string& user, string& pass)
{
	int d = 0, m = 0, y = 0;
	enter_dmy(d, m, y);
	cin.ignore();
	if (check_dmy(d, m, y))
	{
		if (enter_acc(user, pass))
		{
			check_acc_ad(user, pass);
		}
	}
	else enter_dmy(d, m, y);
}
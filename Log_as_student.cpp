#include"LOGIN.h"
#include"Log_as_stu.h"
void check_acc_student(string usr, string psw)
{
	ifstream f;
	f.open("acc_sv.csv");
	string acc = account(usr, psw);
	int c = 0;
	int n = count_acc_in_csv("acc_sv");
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
				cout << "\t\tPress Enter to return -Main Menu- !!!" << endl;
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
void login_as_student(string& user, string& pass)
{
	int d = 0, m = 0, y = 0;
	enter_dmy(d, m, y);
	cin.ignore();
	if (check_dmy(d, m, y))
	{
		if (enter_acc(user, pass))
		{
			check_acc_student(user, pass);
		}
	}
	else enter_dmy(d, m, y);
}
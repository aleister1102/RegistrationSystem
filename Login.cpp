#include "Menu.h"
#include "LOGIN.h"

// Checking
bool check_leap_year(int year)
{
	return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
}
int day_of_month(int month, int year)
{
	switch (month)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12:	return 31;
	case 4:case 6:case 9:case 11: return 30;
	default:
		if (check_leap_year(year))
		{
			return 29;
		}
		else return 28;
		break;
	}
}
bool check_dmy(date dmy)
{
	if (dmy.year <= 0 || dmy.month <= 0)
	{
		return false;
	}
	if (dmy.month < 1 || dmy.month>12)
	{
		return false;
	}
	if (dmy.day <= 0 || dmy.day > day_of_month(dmy.month, dmy.year))
	{
		return false;
	}
	return true;
}
void enter_dmy(date& dmy)
{
	cout << "\t\tEnter day / month / year: " << endl;
	cout << "\t\t";
	cin >> dmy.day; cout << "\t\t";
	cin >> dmy.month; cout << "\t\t";
	cin >> dmy.year;
}

// Password proccess
int enterpass()
{
	cout << "\t\t1.Show your password !!!" << endl;
	cout << "\t\t2.Hide your password !!!" << endl;
	cout << "\t\t";
	return Valid_Data(2);
}
void showpass(string& pass)
{
	cin.ignore();
	cout << "\t\tEnter password (No spacebar and special symbols in your password): ";
	getline(cin, pass);
}
void hidepass(string& pass)
{
	cin.ignore();
	cout << "\t\tEnter password (No spacebar and special symbols in your password): ";
	char a = _getch();
	int i = 0;
	while (a != 13)
	{
		cout << "*";
		if (a >= 65 && a <= 90 || a >= 97 && a <= 122)
		{
			pass += a;
		}
		if (a >= 48 && a <= 57)
		{
			pass += a;
		}
		a = _getch();
	}
}
bool enterpass_proc(int option, string& psw)
{
	if (option == 1)
	{
		psw = "";
		showpass(psw);
		return true;
	}
	else if (option == 2)
	{
		psw = "";
		hidepass(psw);
		cout << endl;
		return true;
	}
	else
	{
		return false;
	}
}
bool enter_acc(user& info)
{
	cin.ignore();
	cout << "\t\tEnter username: ";
	getline(cin, info.username);
	bool k = enterpass_proc(enterpass(), info.password);
	return k;
}

// Count line in csv file
int count_acc(string name)
{
	ifstream f;
	f.open(name+".csv");
	int c = 0;
	while (!f.eof())
	{
		string s1 = "";
		f >> s1;
		c++;
	}
	f.close();
	return c - 1;
}
// Create account
string account(user info)
{
	return info.username + ',' + info.password;
}

// Login as Student
bool check_acc_student(user info)
{
	ifstream f;
	f.open("acc_sv.csv");
	string acc = account(info);
	int c = 0;
	int n = count_acc("acc_sv");
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
				cout << "\t\t"; system("pause");
				return false;
			}
		}
		else
		{
			cout << "\t\tLogin sucessed !!!" << endl;
			cout << "\t\t"; system("pause");
			return true;
			break;
		}
	}
	f.close();
}
bool login_as_student(user &info,date &dmy)
{
	cout << "\t\tLogin as Student" << endl;
	cin.ignore();
	do {
		enter_dmy(dmy);
	} while (check_dmy(dmy) != true);
	if (enter_acc(info))
	{
		return check_acc_student(info);
	}
}
// Login as Admin
bool check_acc_ad(user info)
{
	if (info.password[0] == 'A' && info.password[1] == 'D')
	{
		ifstream f;
		f.open("acc_ad.csv");
		string acc = account(info);
		int c = 0;
		int n = count_acc("acc_ad");
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
					cout << "\t\t"; system("pause");
					return false;
					
				}
			}
			else
			{
				cout << "\t\tLogin sucessed !!!" << endl;
				cout << "\t\t"; system("pause");
				return true;
				break;
			}
		}
		f.close();
	}
	else
	{
		cout << "\t\tWrong password or username !!!" << endl;
		cout << "\t\t"; system("pause");
		return false;
	}
}
bool login_as_admin(user& info,date &dmy)
{
	cout << "\t\tLogin as Admin" << endl;
	do {
		enter_dmy(dmy);
	} while (check_dmy(dmy)!=true);
	if (enter_acc(info))
	{
		return check_acc_ad(info);
	}
}

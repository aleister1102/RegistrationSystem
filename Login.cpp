#include "Header/Menu.h"
#include "Header/File.h"
#include "Header/Login.h"

//Kiểm tra năm nhuận
bool check_leap_year(int year)
{
	return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
}
//Số ngày của tháng
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
//Kiểm tra tính hợp lệ của ngày tháng
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
//Nhập ngày tháng
void enter_dmy(date& dmy)
{
	do {
		cout << "\t\tEnter day / month / year: " << endl;
		cout << "\t\t";
		cin >> dmy.day; cout << "\t\t";
		cin >> dmy.month; cout << "\t\t";
		cin >> dmy.year;
	} while (check_dmy(dmy) != true);
}

string delete_last(string s)
{
	string ss = s;
	int n = size(s) - 1;
	s = "";
	for (int i = 0; i < n; i++)
	{
		s += ss[i];
	}
	return s;
}
int pass_mode()
{
	cout << "\t\t1.Show your password !!!" << endl;
	cout << "\t\t2.Hide your password !!!" << endl;
	cout << "\t\t";
	return Valid_Data(2);
}
bool pass_mode_proc(int option, user& info)
{
	if (option == 1)
	{
		enter_showpass(info);
		return true;
	}
	else if (option == 2)
	{
		enter_hidepass(info);
		cout << endl;
		return true;
	}
	else
	{
		return false;
	}
}
void enter_showpass(user &info)
{
	cin.ignore();
	cout << "\t\tEnter password (No spacebar and special symbols in your password): ";
	enter_data(info.password);
}
void enter_hidepass(user &info)
{
	cin.ignore();
	cout << "\t\tEnter password (No spacebar and special symbols in your password): ";
	string ss = "";
	char a = _getch();
	int i = 0;
	while (a != 13)
	{
		if (a >= 65 && a <= 90 || a >= 97 && a <= 122)
		{
			ss += a;
			cout << "*";
		}
		if (a >= 48 && a <= 57)
		{
			ss += a;
			cout << "*";
		}
		if (a == 8)
		{
			system("cls");
			cout << "\t\tEnter username: "; cout << info.username << endl;
			cout << "\t\t1.Show your password !!!" << endl;
			cout << "\t\t2.Hide your password !!!" << endl;
			cout << "\t\tSelect your option: "; cout << 2;
			cout << "\n\n";
			cout << "\t\tEnter password (No spacebar and special symbols in your password): ";
			ss = delete_last(ss);
			for (int i = 0; i < size(ss); i++)
			{
				cout << "*";
			}
		}
		a = _getch();
	}
	info.password = ss;
}
void enter_data(string& param)
{
	getline(cin, param);
}
bool enter_acc(user& info)
{
	cin.ignore();
	cout << "\t\tEnter username: ";
	enter_data(info.username);
	bool k = pass_mode_proc(pass_mode(), info);
	return k;
}

// Count line in csv file
int count_acc(string acc_path)
{
	ifstream f;
	f.open(acc_path);
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
	string acc_name = "acc_sv";
	string acc_path = ".\\Accounts\\";
	acc_path += (acc_name + ".csv");
	f.open(acc_path);
	string acc = account(info);
	int c = 0;
	int n = Count_line(acc_path);
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
bool login_as_student(user &info)
{
	cout << "\t\tLogin as Student" << endl;
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
		string acc_name = "acc_ad";
		string acc_path = ".\\Accounts\\";
		acc_path += (acc_name + ".csv");
		f.open(acc_path);
		string acc = account(info);
		int c = 0;
		int n = Count_line(acc_path);
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
bool login_as_admin(user& info)
{
	cout << "\t\tLogin as Admin" << endl;
	if (enter_acc(info))
	{
		return check_acc_ad(info);
	}
}

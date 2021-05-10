#include"LOGIN.h"
#include"Log_as_ad.h"
#include"Log_as_stu.h"
int menuMain()
{
	cout << "\t\t\t-Main Menu-"<<endl;
	cout << "\t\t0.Exit" << endl;
	cout << "\t\t1.Login as admin" << endl;
	cout << "\t\t2.Login as student" << endl;
	cout << "\t\t3.Forgot pass" << endl;
	return Valid_Data(4);
}
bool menuMain_proc(int option)
{
	if (option == 0)
	{
		return false;
	}
	else if (option == 1)
	{
		string user = "", name = "";
		login_as_admin(user,name);
		return true;
	}
	else if (option == 2)
	{
		string user = "", name = "";
		login_as_student(user,name);
		return true;
	}
	else
	{
		cout << "\t\tThis is your new pass: toanledz" << endl;
		return false;
	}
}
int main()
{
	bool k = true;
	while (k)
	{
		k = menuMain_proc(menuMain());
	}
	return 0;
}
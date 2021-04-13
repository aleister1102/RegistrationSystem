#include "Menu.h"

//Display main menu
//Return: Choice (int type) of user
int Main_Menu_Disp()
{
	system("cls");
	cout << "\t\t---- Welcome to course registration system ----" << endl;
	cout << "\t\t\t\t 1. Login" << endl;
	cout << "\t\t\t\t 2. Forgot Password ?" << endl;
	cout << "\t\t\t\t 3. About Us" << endl;
	cout << "\t\t\t\t 4. Exit" << endl;
	cout << "\t\t Your choice is (choose from 1 to 4): ";
	return Valid_Data();
}
bool Main_Menu_Proc(int n)
{
	if (n == 1)//Login
	{
		Login_Proc(Login_Disp());
		return true;
	}
	else if (n == 2)//Forgot Pass
	{
		ForgotPass_Proc(ForgotPass_Disp());
		return true;
	}
	else if (n == 3)//About Us
	{
		AboutUs();
		return true;
	}
	else if (n == 4)//Exit
	{
		cout << "EXIT !!!" << endl;
		return false;
	}
}

//Sub menu (display and proccess)
void Login_Proc(int n)
{

}
int Login_Disp()
{
	cout << "Login" << endl;
	system("pause");
	return 0;
}
void ForgotPass_Proc(int n)
{

}
int ForgotPass_Disp()
{
	cout << "Forgot Pass" << endl;
	system("pause");
	return 0;
}
void AboutUs()
{
	cout << "About Us" << endl;
	system("pause");
}

int Valid_Data()
{
	int n = 0; cin >> n;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "\t\t Invalid Input !!!!!!!!" << endl;
			cout << "\t\t Type input again: "; cin >> n;
		}
		if (!cin.fail())
			break;
	}
	return n;
}
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
	return Valid_Data(4);
}
bool Main_Menu_Proc(int option)
{
	if (option == 1)//Login
	{
		bool run = true;
		while (run)
		{
			run = Login_Proc(Login_Disp());
		}
		return true;
	}
	else if (option == 2)//Forgot Pass
	{
		ForgotPass_Proc(ForgotPass_Disp());
		return true;
	}
	else if (option == 3)//About Us
	{
		AboutUs();
		return true;
	}
	else if (option == 4)//Exit
	{
		cout << "EXIT !!!" << endl;
		return false;
	}
}

//Sub menu (display and proccess)
bool Login_Proc(int option)
{
	//If user is administrator
	if (option == 1)
	{
		bool run = true;
		while (run)
		{
			run = Admin_Proc(Admin_Disp());
		}
		return true;
	}
	else if (option == 2)
	{
		Student_Disp();
		return true;
	}
	else return false;
}
int Login_Disp()
{
	system("cls");
	cout << "\t\t LOGIN" << endl;
	cout << "\t\t 1. Admin" << endl;
	cout << "\t\t 2. User" << endl;
	cout << "\t\t 3. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(3);
}
void ForgotPass_Proc(int option)
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

//Admin Menu
int Admin_Disp()
{
	//system("cls");
	cout << "\t\t YOU ARE ADMIN NOW	" << endl;
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Year Section" << endl;
	cout << "\t\t 2. Class Section" << endl;
	cout << "\t\t 3. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(3);
}
bool Admin_Proc(int option)
{
	if (option == 1)
	{
		bool run = true;
		while (run)
		{
			Years_Display();
			run = Year_Proc_Active(Year_Menu_Disp(),2021);
		}
		return true;
	}
	else if (option == 2)
	{
		bool run = true;
		while (run)
		{
			run = Class_Proc_Active(Class_Menu_Disp(),2021);
		}
		return true;
	}
	else
	{
		return false;
		system("cls");
	}
}
//Student Menu
int Student_Disp()
{
	cout << "\t\t Student section" << endl;
	cout << "\t\t 1. Exit" << endl;
	return Valid_Data(1);
}

//Year Menu
int Year_Menu_Disp()
{
	//system("cls");
	cout << "\t\t YEAR SECTION" << endl;
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Create new year" << endl;
	cout << "\t\t 2. Delete year" << endl;
	cout << "\t\t 3. Delete all years" << endl;
	cout << "\t\t 4. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(4);
}
//Class Menu
int Class_Menu_Disp()
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Add new class" << endl;
	cout << "\t\t 2. Delete class" << endl;
	cout << "\t\t 3. Clear classes" << endl;
	cout << "\t\t 4. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(4);
}
//Semester Menu
int Semester_Menu_Disp()
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Add new semester" << endl;
	cout << "\t\t 2. Select semester" << endl;
	cout << "\t\t 3. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(3);
}
//Student Menu
int Student_Menu_Disp()
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Add new student(s)" << endl;
	cout << "\t\t 2. Delete student(s)" << endl;
	cout << "\t\t 3. Watch student(s)" << endl;
	cout << "\t\t 4. Exit" << endl;
	cout << "Select option: ";
	return Valid_Data(3);
}
//Department
int Department_Menu_Disp()
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Information Technology" << endl;
	cout << "\t\t 2. Geology" << endl;
	cout << "\t\t 3. Electronics & Telecommunication" << endl;
	cout << "\t\t 4. Chemistry" << endl;
	cout << "\t\t 5. Material Science & Technology" << endl;
	cout << "\t\t 6. Environment" << endl;
	cout << "\t\t 7. Biology" << endl;
	cout << "\t\t 8. Mathematics" << endl;
	cout << "\t\t 9. Physics" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(9);
}

int Valid_Data(int limit)
{
	int n = 0; 
	do 
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "\t\t Invalid Input !!!!!!!!" << endl;
			cout << "\t\t Type input again: "; cin >> n;
		}
		else {
			cin >> n;
		}
	} while (n > limit || n < 0);
	cout << endl;
	return n;
}
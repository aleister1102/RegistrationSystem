#include "Header/Menu.h"
#include "Header/Year.h"
#include "Header/Class.h"
#include "Header/Node Process.h"
#include "Header/Login.h"
#include "Header/Password.h"
#include "Header/Course.h"
#include "Header/Convert.h"
#include "Header/File.h"
#include "Header/Semester.h"
#include "Header/Enroll.h"


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
		if (n > limit)
		{
			cout << "\t\t Input data is Over Limited" << endl;
			cout<<"\t\t ";
		}
		if (n == -1) {
			cout << "\t\t You have pressed the hidden button to stop the program ^^ " << endl;
			cout << "\t\t "; system("pause");
			return n;
		}
	} while (n > limit || n < 0);
	cout << endl;
	return n;
}

//Display main menu
//Return: Choice (int type) of user
int Main_Menu_Disp()
{
	system("cls");
	cout << "\t\t---- Welcome to course registration system ----" << endl;
	cout << "\t\t\t\t 1. Login" << endl;
	cout << "\t\t\t\t 2. About Us" << endl;
	cout << "\t\t\t\t 3. Exit" << endl;
	cout << "\t\t Your choice is (choose from 1 to 4): ";
	return Valid_Data(3);
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
	else if (option == 2)//About Us
	{
		AboutUs();
		return true;
	}
	else if (option == 3)//Exit
	{
		cout << "\t\t EXIT !!!" << endl;
		return false;
	}
}


//Sub menu (display and proccess)
bool Login_Proc(int option)
{
	bool run = true;
	user account; date dmy;
	SV info;
	info.faculty = "CNTT";
	info.id = 20120386;
	info.name = "Le Phuoc Toan";
	//If user is administrator
	if (option == 1)
	{
		/*run = login_as_admin(info);*/
		////////////Login system: off/////////////////
		enter_dmy(dmy);
		system("cls");
		
		while (run)
		{
			run = Display_Mode_Admin(account, dmy);
		}
		return true;
	}
	else if (option == 2)
	{
		/*run = login_as_student(info);*/
		//Login system: off
		enter_dmy(dmy);
		system("cls");
		
		while (run)
		{
			run = Display_Mode_Student(info,dmy);
		}
		return true;
	}
	else if (option == 3)
	{
		cin.ignore();
		change_pass();
		cout << "\t\t "; system("pause");
		return true;
	}
	else if (option == 4)
	{
		cin.ignore();
		forgot_pass();
		cout << "\t\t "; system("pause");
		return true;
	}
	else {
		return false;
	}
}
int Login_Disp()
{
	system("cls");
	cout << "\t\t LOGIN" << endl;
	cout << "\t\t 1. As Admin" << endl;
	cout << "\t\t 2. As Student" << endl;
	cout << "\t\t 3. Change Password(Only student)" << endl;
	cout << "\t\t 4. Forgot password(Only student)" << endl;
	cout << "\t\t 5. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(5);
}
void AboutUs()
{
	cout << "About Us" << endl;
	system("pause");
}

//Admin Menu
bool Display_Mode_Admin(user info, date dmy)
{
	if (dmy.month ==7 || dmy.month == 8)
	{
		cout << "\t\t Insert grade function here" << endl;
		cout << "\t\t "; system("pause");
		return false;
	}
	else
	{
		return Admin_Proc_Begin(Admin_Disp_Begin(), info, dmy);
	}
}
int Admin_Disp_Begin()
{
	system("cls");
	cout << "\t\t YOU ARE ADMIN NOW	" << endl;
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Year Section" << endl;
	cout << "\t\t 2. Class Section" << endl;
	cout << "\t\t 3. Semester Section" << endl;
	cout << "\t\t 4. Course Section" << endl;
	cout << "\t\t 5. Student Section" << endl;
	cout << "\t\t 6. Log Out" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(6);
}
bool Admin_Proc_Begin(int option,user info,date dmy)
{
	if (option == 1)
	{
		bool run = true;
		while (run)
		{
			Years_Display();
			run = Year_Proc(Year_Menu_Disp(),dmy.year);
		}
		return true;
	}
	else if (option == 2)
	{
		bool run = true;
		while (run)
		{
			string year_name = Year_Selection();
			string pre_folder = ".\\Years\\";
			string year_path = Make_Path(pre_folder, year_name);
			if (year_name == "!")  return true;
			Classes_Display(year_path);
			run = Class_Proc_Active(year_name,Class_Menu_Disp());
		}
		return true;
	}
	else if (option == 3)
	{
		bool run = true;
		while(run)
		{
			string year_name = Year_Selection();
			run = Semester_Proc(Semester_Menu_Disp(), year_name,dmy);
		}

	}
	else if (option == 4)
	{
		bool run = true;
		
		while (run)
		{
			run = Course_Proc(Course_Menu_Disp());
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
bool Display_Mode_Student(SV info, date dmy)
{
	if (dmy.month == 9)
	{
		return Student_Proc_Begin(Student_Disp_Begin(), info, dmy);
	}
	else if (dmy.month == 7)
	{
		cout << "\t\t Insert grade function here" << endl;
		cout << "\t\t "; system("pause");
		return false;
	}
	else
	{
		cout << "\t\t You can not do anything this time" << endl;
		cout << "\t\t "; system("pause");
		return false;
	}

}
int Student_Disp_Begin()
{
	//system("cls");
	cout << "\t\t YOU ARE STUDENT NOW	" << endl;
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Enroll Classes" << endl;
	cout << "\t\t 2. Log out" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(2);
}
bool Student_Proc_Begin(int option,SV info,date dmy)
{
	if(option == 1){
		bool run = true;
		while(run){
			run = Enroll_MenuProc(Enroll_MenuDisp(info),info);
		}
		return true;
	}
	else{
		return false;
	}
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
	cout << "\t\t 0. Back " << endl;
	cout << "\t\t 1. Add new class" << endl;
	cout << "\t\t 2. Delete class" << endl;
	cout << "\t\t 3. Clear classes" << endl;
	cout << "\t\t 4. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(4);
}
int Class_Create_Mod_Menu()
{
	cout << "\t\t CREATE CLASS SECTION " << endl;
	cout << "\t\t 1. Import classes from files" << endl;
	cout << "\t\t 2. Add single class" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(2);
}
//Semester Menu
int Semester_Menu_Disp()
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Add new semester" << endl;
	cout << "\t\t 2. Delete semesters" << endl;
	cout << "\t\t 3. View semesters" << endl;
	cout << "\t\t 4. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(4);
}
//Course Menu
int Course_Menu_Disp() 
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Add new course" << endl;
	cout << "\t\t 2. Update course" << endl;
	cout << "\t\t 3. Delete course" << endl;
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
//Training System 
int Training_System_Menu_Disp()
{
	cout << "\t\t Choose your training system: " << endl;
	cout << "\t\t 1.Popular" << endl;
	cout << "\t\t 2.High Quality" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(2);
}

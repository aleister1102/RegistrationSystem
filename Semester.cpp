#include"Menu.h"
void Create_Semester()
{
	cout << "Create semester function" << endl;
}
void Semester_Disp()
{
	cout << "Semester dipslay function" << endl;
}
//Process semester task
bool Semester_Proc_Active(int option)
{
	if (option == 1)
	{
		Create_Semester();
		return true;
	}
	else if (option == 2)
	{
		Semester_Disp();
		return true;
	}
	else
	{
		cout << "EXIT" << endl;
		return false;
	}
}
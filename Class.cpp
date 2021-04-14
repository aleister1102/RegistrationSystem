#include"Menu.h"

void Create_Class()
{
	cout << "Create class function" << endl;
}
void Class_Disp()
{
	cout << "Class dipslay function" << endl;
}
void Delete_Class()
{

}
//Process class task
bool Class_Proc_Active(int option)
{
	if (option == 1)
	{
		Create_Class();
		return true;
	}
	else if (option == 2)
	{
		Delete_Class();
		return true;
	}
	else if (option == 3)
	{
		Class_Disp();
		return true;
	}
	else
	{
		cout << "EXIT" << endl;
		return false;
	}
}
#include"Menu.h"
#include"Year.h"

void Create_Class()
{
	cout << "\t\t Create class function" << endl;
}
void Delete_Class()
{

}
void Select_Class()
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
		Select_Class();
		return true;
	}
	else if(option ==4)
	{
		cout << "EXIT" << endl;
		return false;
	}

}
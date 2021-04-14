#include "Menu.h"

void Create_Year()
{
	cout << "\t\t Create year function" << endl;
}
void Year_Display()
{
	cout << "\t\t Year display function" << endl;
	cout << "\t\t Choose your option: " << endl;
}
//Process year task
bool Year_Proc_Active(int option)
{
	if (option == 1)
	{
		Create_Year();
		system("cls");
		return true;
	}
	else if (option == 2)
	{
		Year_Display();
		system("cls");
		return true;
	}
	else
	{
		cout << "\t\t EXIT" << endl;
		system("cls");
		return false;
	}
}
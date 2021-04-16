#include"Menu.h"
#include"Year.h"

string Create_Class(string classes,int time)
{
	cout << "\t\t CREATE CLASS SECTION " << endl;
	cout << "\t\t 1. Import classes from files" << endl;
	cout << "\t\t 2. Add single class" << endl;
	cout << "\t\t Select option: ";
	int choice = Valid_Data(2);
	FILE* fileInput;

	string name;
	if (choice == 2)
	{
		do {
			cout << "\t\t Enter name of class: ";
			getline(cin, name, '\n');
			for (auto& c : name) c = toupper(c);
		} while (name.length() > 5 || name.length() <= 0 );
	}

	stringstream ss; string period;
	ss << time%100; ss >> period;
	name = period + name + ".csv";

	fileInput = fopen(name.c_str(), "a+");
	fclose(fileInput);

	cout << "\t\t File name: " << name << endl;
	cout << "\t\t Class created successfully" << endl;
	cout << "\t\t "; system("pause");
	return name;
}
void Delete_Class()
{

}
void Select_Class()
{

}
//Process class task
bool Class_Proc_Active(int option,string classes)
{
	if (option == 1)
	{
		Create_Class(classes,2021);
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
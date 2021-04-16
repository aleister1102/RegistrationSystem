#include"Menu.h"
#include"Year.h"

//Get code name for each department
string Department_Name(int depart)
{
	switch (depart)
	{
	case 1: {return "CTT"; break; }
	case 2: {return "DCH"; break; }
	case 3: {return "DTV"; break; }
	case 4: {return "HOH"; break; }
	case 5: {return "KVL"; break; }
	case 6: {return "KMT"; break; }
	case 7: {return "SHH"; break; }
	case 8: {return "TTH"; break; }
	default: {return "VLH"; break; }
	}
}
//Put class path into list
void Input_Class(string store, string path)
{
	cout << "\t\t Save class at" << store << endl;
	fstream f(store, ios::app | ios::out);
	f << path << endl;
	f.close();

}
string Create_Class(string classes, int time)
{
	cout << "\t\t CREATE CLASS SECTION " << endl;
	cout << "\t\t 1. Import classes from files" << endl;
	cout << "\t\t 2. Add single class" << endl;
	cout << "\t\t Select option: ";
	int choice = Valid_Data(2);
	FILE* fileInput;

	string name; int n = 0;
	if (choice == 2)
	{
		int depart = Department_Menu_Disp();
		do {
			cout << "\t\t Enter order of class: ";
			cin >> n;
		} while (n < 0 || n>5);
		name = Department_Name(depart);
	}
	else {

	}
	
	stringstream ss; string period;
	ss << time % 100; ss >> period;

	stringstream ss2; string order;
	ss2 << n; ss2 >> order;
	name = period + name + order + ".csv";

	
	string path = ".\\Classes\\"+ParsePath(classes).substr(0, 9) + "\\";
	path = path + name;
	cout << path << endl;

	fileInput = fopen(path.c_str(), "a+");
	fclose(fileInput);

	cout << "\t\t File name: " << name << endl;
	cout << "\t\t Class created successfully" << endl;
	cout << "\t\t "; system("pause");

	Input_Class(classes, name);

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
		return true;
	}
	else if(option ==4)
	{
		cout << "EXIT" << endl;
		return false;
	}

}

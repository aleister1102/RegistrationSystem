#include "Menu.h"
#include "Year.h"

////Check the existence of file//
//Input: path of file in string type
//Return: True if file is exist and false if not
bool File_Exist(string path)
{
	fstream fileInput(path);
	if (fileInput.fail()) {
		cout << "\t\t File does not exist" << endl;
		return false;
	}
	else {
		cout << "\t\t File exists" << endl;
		return true;
	}
}

////Add year into year list//
//Input: path of store file and path of year file
void Input_Year(string store,string path)
{
	fstream f(store,ios::app|ios::out);
	f << path << endl;
	f.close();
}
////Create new year file with limited time//
//Input: limit of time that can be used to create
//Return: path of year file that have been created
string Create_Year(int time)
{
	int begin = 0 , end = 0;
	string name1, name2, path_temp;
	FILE* fileInput;

	cout << "\t\t CREATE YEAR SECTION "<<endl;
	do {
		stringstream ss1, ss2;
		cout << "\t\t Created school year from: ";
		begin = Valid_Data(time);
		end = begin + 1;

		//Transform name into file path
		ss1 << begin; ss1 >> name1;
		ss2 << end; ss2 >> name2;
		path_temp = name1 + "-" + name2 + ".csv";
	} while (File_Exist(path_temp));

	const char* path = path_temp.c_str();//Convert to const char *
	//Create new file
	fileInput= fopen(path,"a+");
	fclose(fileInput);
	//Put file into store file
	Input_Year("Years.csv", path);
	cout << "\t\t School year created successfully" << endl;
	cout << "\t\t "; system("pause");
	return path;
}

////Class option orientation//
void Class_Orientation(string classes)
{
	bool run = true;
	do {
		 run = Class_Proc_Active(Class_Menu_Disp());
	} while (run);
}
////Year orientation
void Year_Orientation(string years, int choice)
{
	string classes; int i = 1;
	fstream f(years, ios::in);

	while (!f.eof()) {
		string read;
		f >> read;
		if (i++ == choice)
		{
			classes = read;
			Classes_Display(classes);
			Class_Orientation(classes);
			break;
		}
	}
	f.close();
}
////Classes displaying//
int Classes_Display(string classes)
{
	if (File_Exist(classes) == false)
	{
		return 0;
	}
	system("cls");
	cout << "\t\t CREATED CLASS: " << endl;
	fstream f(classes, ios::in); int i = 1;

	while (!f.eof())
	{
		string read;
		f >> read;
		if (read != "")
		{
			cout << "\t\t " << i++ << ". " << read << endl;
		}
	}
	f.close();
	return 1;
}

////Year displaying//
void Years_Display(string years)
{
	system("cls");
	cout  << "\t\t CREATED YEARS: " << endl;
	fstream f(years,ios::in);
	int i = 1;

	cout << "\t\t 0. Back: " << endl;
	while (!f.eof()) {
		string read;
		f >> read;
		if (read != "") {
			cout << "\t\t " << i++ << ". " << read << endl;
		}
	}
	f.close();

	cout << "\t\t Choose year: ";
	int choice = Valid_Data(i);
	if (choice != 0)
	{
		Year_Orientation(years, choice);
	}
}
////Process year task//
bool Year_Proc_Active(int option)
{
	int time = 2021;
	if (option == 1)
	{
		Create_Year(time);
		system("cls");
		return true;
	}
	else if (option == 2)
	{
		Years_Display("Years.csv");
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
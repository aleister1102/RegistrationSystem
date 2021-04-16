#include "Menu.h"
#include "Year.h"
#include "Node Process.h"
#include <direct.h>
#include <filesystem>

//Delete directory
void Delete_Directory(string dir)
{
	dir = "rmdir /s /q " + dir;
	system(dir.c_str());
}
////Create new directory contain classes//
string Create_Directory(string classes)
{
	string dir = ".\\Classes\\" + ParsePath(classes).substr(0, 9) + "\\";
	cout << "\t\t Directory path: " << dir << endl;
	// Creating a directory
	if (_mkdir(dir.c_str()) == -1)
		cerr << "\t\t Error :  " << strerror(errno) << endl;

	else
		cout << "\t\t Directory created" << endl;
	return dir;
}

////Parse path of string//
string ParsePath(string s)
{
	int pos = s.find_last_of("\\", strlen(s.c_str()));
	return s.substr(pos + 1);
}
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
void Input_Year(string store, string path)
{

	path = ParsePath(path);
	fstream f(store, ios::app | ios::out);
	f << path << endl;
	f.close();

}
////Create new year file with limited time//
//Input: limit of time that can be used to create
//Return: path of year file that have been created
string Create_Year(int time)
{
	int begin = 0, end = 0;
	string name1, name2, path_temp;
	FILE* fileInput;

	cout << "\t\t CREATE YEAR SECTION " << endl;
	do {
		stringstream ss1, ss2;
		cout << "\t\t Created school year from: ";
		begin = Valid_Data(time);
		end = begin + 1;

		//Transform name into file path
		ss1 << begin; ss1 >> name1;
		ss2 << end; ss2 >> name2;
		path_temp = ".\\Years\\" + name1 + "-" + name2 + ".csv";
	} while (File_Exist(path_temp));

	//Create new folder
	string dir = Create_Directory(path_temp);
	//Create new file
	fileInput = fopen(path_temp.c_str(), "a+");
	fclose(fileInput);
	//Put file into store file
	Input_Year("Years.csv", path_temp.c_str());
	cout << "\t\t School year created successfully" << endl;
	cout << "\t\t "; system("pause");
	return path_temp;
}

////Class option //
void Class_Orientation(string classes)
{
	bool run = true;
	do {

		 run = Class_Proc_Active(Class_Menu_Disp(),classes);
		 system("cls");

	} while (run);
}
////Year orientation
void Year_Orientation(string years, int quanti)
{
	cout << "\t\t Choose year: ";
	int choice = Valid_Data(quanti);

	string classes; int i = 1;
	fstream f(years, ios::in);

	while (!f.eof()) {
		string read;
		f >> read;
		if (i++ == choice)
		{
			classes = ".\\Years\\" + read;
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

////Input Year from node to file after delete//
void ReInput_Year(string years, yrs list)
{
	yr* move = list.head;
	fstream f(years, ios::in | ios::out);
	while (move->next != nullptr)
	{
		f << ParsePath(move->path) << endl;
		move = move->next;
	}
	f.close();
}
////Year_Delete////
void Year_Delete(string years, int quanti)
{
	cout << "\t\t Choose year: ";
	int choice = Valid_Data(quanti);

	int i = 1;
	fstream f(years, ios::in | ios::out);
	stringstream ss;
	yrs list = Init_List();

	while (!f.eof()) {

		string read;
		f >> read;
		read = ".\\Years\\" + read;
		yr* node = Init_Node(read);
		Add_Last(list, node);

		if (i++ == choice)
		{
			//Just deleted file in directory, not in Years.csv
			remove(read.c_str());
			//Delete in file by delete nodes
			Remove_Info(list, read);
			//Delete directory
			string dir = ".\\Classes\\" + ParsePath(read).substr(0, 9) + "\\";
			Delete_Directory(dir);
		}
	}
	f.close();
	remove(years.c_str());
	f.open(years.c_str(), ios::out);
	f.close();
	ReInput_Year(years, list);

}
////Delete all years//
void Year_Clear(string years) {
	cout << "\t\t All years will be deleted !!!!" << endl;
	cout << "\t\t Are you sure ???" << endl;
	cout << "\t\t Press 0 for accepting, 1 for not:  ";
	int n; cin >> n;
	if (n == 0)
	{
		fstream f(years, ios::in | ios::out);
		int i = 1;

		while (!f.eof()) {

			string read;
			f >> read;

			//Delete directories
			string dir = ".\\Classes\\" + read.substr(0, 9) + "\\";
			dir = "rmdir /s /q " + dir;
			system(dir.c_str());

			//Delete files
			read = ".\\Years\\" + read;
			remove(read.c_str());

		}
		f.close();
		remove(years.c_str());
		f.open(years.c_str(), ios::out);
		f.close();
		string dir = ".\\Classes\\";
		_mkdir(dir.c_str());
	}
}

//Year sorting
void Year_Sort(string years)
{
	int i = 1;
	fstream f(years, ios::in | ios::out);
	stringstream ss;
	yrs list = Init_List();

	while (!f.eof())
	{
		string read;
		f >> read;
		yr* node = Init_Node(read);
		Add_Last(list, node);
	}
	f.close();
	SortAscen_List(list);
	remove(years.c_str());
	f.open(years.c_str(), ios::out);
	f.close();
	ReInput_Year(years, list);
}

////Year displaying//
int Years_Display(string years)
{
	system("cls");
	Year_Sort(years);
	cout << "\t\t CREATED YEARS: " << endl;
	fstream f(years, ios::in);
	int i = 1;

	cout << "\t\t 0. Back " << endl;
	while (!f.eof()) {
		string read;
		f >> read;
		if (read != "") {
			cout << "\t\t " << i++ << ". " << read << endl;
		}
	}
	f.close();
	return i;
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
		int quanti = Years_Display("Years.csv");
		Year_Orientation("Years.csv", quanti);
		system("cls");
		return true;
	}
	else if (option == 3)
	{
		int quanti = Years_Display("Years.csv");
		Year_Delete("Years.csv", quanti);
		system("cls");
		return true;
	}
	else if (option == 4)
	{
		Year_Clear("Years.csv");
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
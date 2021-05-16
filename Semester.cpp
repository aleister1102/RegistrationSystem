#include "Semester.h"
#include "Menu.h"
#include "Year.h"
#include "Class.h"
#include "Node Process.h"

//Semester Creation
bool Name_InFile(string store,string name)
{
	fstream f;
	f.open(store.c_str(), ios::in|ios::out);
	
	while (!f.eof())
	{
		string read;
		f >> read;
		if (name == read)
		{
			return true;
			break;
		}
	}
	f.close();
	return false;
}
string Season_ofSemester(int choice)
{
	if (choice == 1)
		return "-Autumn.csv";
	else if (choice == 2)
		return "-Summer.csv";
	else if (choice == 3)
		return "-Fall.csv";
}
string Semester_ToPath(string year_name)
{
	return ".\\Semesters\\" + year_name.substr(0, 9) + "\\";
}
void Create_Semester(int limited_year,string year_name)
{
	string seasons[3] = { "-Autumn.csv","-Summer.csv","-Fall.csv" };
	string semester_path = Semester_ToPath(year_name) + CSV_ToName(year_name);
	string semesters_path = ".\\Semesters\\" + string("Semesters.csv");
	FILE* fileInput;

	bool check = Name_InFile(semesters_path, year_name);
	if (check != true) {
		cout << "\t\t Will add semester" << endl;
		//Put file into store file
		Input_Years(semesters_path, year_name.c_str());
		//Create new file
		for (int i = 1; i <= 3; i++)
		{
			string temp = semester_path + seasons[i - 1];
			fileInput = fopen(temp.c_str(), "a+");
			fclose(fileInput);
		}
	}

	cout << "\t\t Semester year created successfully" << endl;
	cout << "\t\t "; system("pause");
}
//Semester Deleting
void Semester_Delete(string year_name)
{
	string semesters_path = ".\\Semesters\\" + string("Semesters.csv");
	paths list = Init_List();
	if (Name_InFile(semesters_path, year_name) == false)
	{
		cout << "\t\t This year does not have any semesters !!" << endl;
		cout << "\t\t "; system("pause");
		return;
	}
	fstream f(semesters_path, ios::in | ios::out);

	while (!f.eof()) {

		//Read year file's name from "Semester.csv"
		string read;
		f >> read;
		//Add year file's name into list of nodes
		if (read != year_name)
		{
			path* node = Create_Node(year_name);
			Add_Last(list, node);
		}
	}
	f.close();

	//Just deleted file in directory, not in Years.csv
	string dir = Semester_ToPath(year_name);
	Delete_Directory(dir);
	
	//Delete old "Years.csv" and create the new one
	remove(semesters_path.c_str());
	f.open(semesters_path.c_str(), ios::out);
	f.close();
	//Copy year's name to "Years.csv" from list
	ReInput_fromList(semesters_path, list);
}\
//Semester Displaying
void Semesters_Display(string year_name)
{
	system("cls");
	string seasons[3] = { "-Autumn.csv","-Summer.csv","-Fall.csv" };
	string semesters_path = ".\\Semesters\\" + string("Semesters.csv");
	if (Name_InFile(semesters_path, year_name) ==false )
	{
		cout << "\t\t This year does not have any semesters !!" << endl;
		cout << "\t\t "; system("pause");
		return;
	}
	cout << "\t\t CREATED SEMESTERS: " << endl;
	cout << "\t\t 0. Back" << endl;
	for (int i = 1; i <= 3; i++)
	{
		cout << "\t\t " << i << ". " << CSV_ToName(year_name) + seasons[i - 1] << endl;
	}
	cout << "\t\t "; system("pause");
}
//Process semester task
bool Semester_Proc(int option,int limited_year,string year_name)
{
	if (option == 1)
	{
		Create_Semester(limited_year,year_name);
		system("cls");
		return true;
	}
	else if (option == 2)
	{
		Semester_Delete(year_name);
		system("cls");
		return true;
	}
	else if (option == 3)
	{
		Semesters_Display(year_name);
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
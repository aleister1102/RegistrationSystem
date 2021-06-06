#include "Semester.h"
#include "Menu.h"
#include "Year.h"
#include "Class.h"
#include "File.h"
#include "Convert.h"
#include "Node Process.h"

//Semester Creation
void Create_Semester(int limited_year,string year_name)
{
	string seasons[3] = { "-Autumn","-Summer","-Fall" };
	string pre_folder = ".\\Semesters\\" + Path_ToName(year_name) + "\\";
	FILE* fileInput;

	//Create new file
	for (int i = 1; i <= 3; i++)
	{
		string temp = Extension(pre_folder + year_name + seasons[i - 1],1);
		fileInput = fopen(temp.c_str(), "a+");
		fclose(fileInput);
		Save_ToCSVLine("Years.csv", year_name.c_str(),Int_ToString(i));
	}

	cout << "\t\t Semester year created successfully" << endl;
	cout << "\t\t "; system("pause");
}
//Semester Deleting
void Semester_Delete(string year_name)
{
	string semesters_path = ".\\Semesters\\" + string("Semesters.csv");
	names list = Init_List();

	fstream f(semesters_path, ios::in | ios::out);

	while (!f.eof()) {

		//Read year file's name from "Semester.csv"
		string read;
		f >> read;
		//Add year file's name into list of nodes
		if (read != year_name)
		{
			name* node = Create_Node(read);
			Add_Last(list, node);
		}
	}
	f.close();

	//Just deleted file in directory, not in Years.csv
	//string dir = Semester_ToPath(year_name);
	//Directory_Delete(dir);
	
	//Delete old "Years.csv" and create the new one
	remove(semesters_path.c_str());
	f.open(semesters_path.c_str(), ios::out);
	f.close();
	//Copy year's name to "Years.csv" from list
	ReInput_fromList(semesters_path, list);
}
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
		cout << "\t\t " << i << ". " << Extension(year_name,2) + seasons[i - 1] << endl;
	}
	cout << "\t\t "; system("pause");
}
//Process semester task
bool Semester_Proc(int option,int limited_year,string year_name)
{
	if (option == 1)
	{
		string run = Browse_and_CreateFolder("Years.csv", ".\\Semesters\\", year_name);
		if (run == "!") return true;
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
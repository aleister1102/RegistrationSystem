#include "Menu.h"
#include "Year.h"
#include "Class.h"
#include "Node Process.h"

//Check the existence of file
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

//Add year into year list
//Input: path of store file and path of year file
void Input_Years(string store, string year_path)
{
	string year_name = Path_ToYear(year_path);
	fstream f(store, ios::app | ios::out);
	f << year_name << endl;
	f.close();
}
//Convert from year path to year name
string Path_ToYear(string s)
{
	int pos = s.find_last_of("\\", strlen(s.c_str()));
	return s.substr(size_t(pos) + 1);
}
//Convert from year number to year file path
string Year_ToPath(int begin, int end)
{
	stringstream ss1, ss2;
	string name1, name2;
	//Transform name into year file path
	ss1 << begin; ss1 >> name1;
	ss2 << end; ss2 >> name2;
	return   ".\\Years\\" + name1 + "-" + name2 + ".csv";
}
//Create new year file with limited time
//Input: limit of time that can be used to create
//Return: path of year file that have been created
string Create_Year(int year)
{
	int begin, end;
	string years_path;
	FILE* fileInput;

	cout << "\t\t CREATE YEAR SECTION " << endl;
	do {
		cout << "\t\t Created school year from: ";
		begin = Valid_Data(year);
		end = begin + 1;

		years_path = Year_ToPath(begin, end);
	} while (File_Exist(years_path));

	//Create new file
	fileInput = fopen(years_path.c_str(), "a+");
	fclose(fileInput);
	//Put file into store file
	Input_Years("Years.csv", years_path.c_str());

	cout << "\t\t School year created successfully" << endl;
	cout << "\t\t "; system("pause");
	return years_path;
}

//Year_Delete
void Year_Delete(int quanti)
{
	cout << "\t\t Choose year: ";
	int choice = Valid_Data(quanti);

	int i = 1;
	string years_path = "Years.csv",year_path, year_name;
	paths list = Init_List();
	fstream f(years_path, ios::in | ios::out);

	while (!f.eof()) {
		//Read year file's name from "Years.csv"
		f >> year_name;
		//Add year file's name into list of nodes
		path* node = Create_Node(year_name);
		Add_Last(list, node);

		if (i++ == choice)
		{
			year_path = ".\\Years\\" + year_name;
			//Just deleted file in directory, not in Years.csv
			remove(year_path.c_str());
			//Delete in file by deleting node(s) in list
			Remove_Info(list, year_name);
		}
	}
	f.close();
	//Delete old "Years.csv" and create the new one
	remove(years_path.c_str());
	f.open(years_path.c_str(), ios::out);
	f.close();
	//Copy year's name to "Years.csv" from list
	ReInput_fromList("Years.csv", list);
	
	string dir = ".\\Classes\\"
		+ Path_ToYear(year_path).substr(0, 9)
		+ "\\"; //Have to use this syntax to accomplish folder path
	Delete_Directory(dir);
	
}
//Delete all years
void Year_Clear(string years)
{
	cout << "\t\t All years will be deleted !!!!" << endl;
	cout << "\t\t Are you sure ???" << endl;
	cout << "\t\t Press 0 for accepting, 1 for not:  ";
	int n; cin >> n;


	string year_name, year_path;
	if (n == 0)
	{
		fstream f(years, ios::in | ios::out);
		int i = 1;

		while (!f.eof()) {
			
			f >> year_name;

			//Delete files
			year_path = ".\\Years\\" + year_name;
			remove(year_path.c_str());
			//Delete class folder
			string dir = ".\\Classes\\"
				+ Path_ToYear(year_path).substr(0, 9)
				+ "\\"; //Have to use this syntax to accomplish folder path
			Delete_Directory(dir);
		}
		f.close();
		//Remake a new "Years.csv"
		remove(years.c_str());
		f.open(years.c_str(), ios::out);
		f.close();
	}
}

//Year sorting
void Year_Sort()
{
	int i = 1;
	string years_path = "Years.csv";
	fstream f(years_path, ios::in | ios::out);
	stringstream ss;
	paths list = Init_List();

	while (!f.eof())
	{
		string read;
		f >> read;
		//Add info into list of nodes
		path* node = Create_Node(read);
		Add_Last(list, node);
	}
	f.close();
	SortAscen_List(list);
	//Remake a new "Years.csv"
	remove(years_path.c_str());
	f.open(years_path.c_str(), ios::out);
	f.close();
	ReInput_fromList(years_path, list);
}
//Year displaying
int Years_Display()
{
	system("cls");
	Year_Sort();
	cout << "\t\t CREATED YEARS: " << endl;

	fstream f("Years.csv", ios::in);
	int i = 1;

	//Reading Years information from "Years.csv"
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

//Process year task
bool Year_Proc_Active(int option, int time)
{
	if (option == 1)
	{
		Create_Year(time);
		system("cls");
		return true;
	}
	else if (option == 2)
	{
		int quanti = Years_Display();
		Year_Delete(quanti);
		system("cls");
		return true;
	}
	else if (option == 3)
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
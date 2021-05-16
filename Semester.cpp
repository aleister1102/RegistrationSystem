#include "Semester.h"
#include "Menu.h"
#include "Year.h"
#include "Node Process.h"

string Semester_ToPath(string year_name, int season)
{
	string season_name;
	string prefix = ".\\Semesters\\" + year_name.substr(0, 9) + "\\";
	string semester_name = year_name.substr(0, 9) + "-";
	if (season == 1)
		season_name = "Autumn.csv";
	else if (season == 2)
		season_name = "Summer.csv";
	else if (season == 3)
		season_name = "Fall.csv";
	return prefix + semester_name + season_name;
}
string Create_Semester(int limited_year,string year_name)
{
	int season = Season_Disp();
	string semester_path = Semester_ToPath(year_name, season);
	string semesters_path = ".\\Semesters\\";
	FILE* fileInput;

	//Create new file
	fileInput = fopen(semester_path.c_str(), "a+");
	fclose(fileInput);

	//Put file into store file
	Input_Years(semesters_path + "Semesters.csv", year_name.c_str());

	cout << "\t\t Semester year created successfully" << endl;
	cout << "\t\t "; system("pause");
	return semester_path;
}

void Semester_Sort()
{
	int i = 1;
	string semesters_path = "Semesters.csv";
	fstream f(semesters_path, ios::in | ios::out);
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
	remove(semesters_path.c_str());
	f.open(semesters_path.c_str(), ios::out);
	f.close();
	ReInput_Semester(list);
}
void ReInput_Semester(paths list)
{
	path* move = list.head;
	fstream f("Semesters.csv", ios::in | ios::out);
	while (move->next != nullptr)
	{
		f << move->info << endl;
		move = move->next;
	}
	f.close();
}
int Semesters_Display(string year_path)
{

	system("cls");
	Semester_Sort();
	cout << "\t\t CREATED SEMESTERS: " << endl;

	fstream f(year_path, ios::in);
	int i = 1;

	//Reading Years information from "Semester.csv"
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
int Season_Disp()
{

	cout << "\n\n\t\t 1. Semester 1 - Autumn" << endl;
	cout << "\t\t 2. Semester 2 - Summer" << endl;
	cout << "\t\t 3. Semester 3 - Fall" << endl;
	cout << "\t\t Choose season: ";
	return Valid_Data(3);
}

int Semester_Disp()
{
	cout << "\t\t Choose option " << endl;
	cout << "\t\t 1. View cousres" << endl;
	cout << "\t\t 2. Add course" << endl;
	cout << "\t\t 3. Delete course" << endl;
	cout << "\t\t 4. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(4);
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
		system("cls");
		return true;
	}
	else if (option == 3)
	{
		Semester_Disp();
		return true;
	}
	else
	{
		cout << "EXIT" << endl;
		return false;
	}
}
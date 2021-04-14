#include "Menu.h"
#include "Year.h"
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
void Input_Year(string store,string path)
{
	const char* store_char = store.c_str();
	const char* path_char = path.c_str();
	path.c_str();
	FILE* s;
	s = fopen(store_char,"a");
	fputs(path_char, s);
	fclose(s);
}
string Create_Year(int time)
{
	int begin = 0 , end = 0;
	stringstream ss1, ss2;
	string name1, name2, path_temp;
	
	FILE* fileInput;
	cout << "\t\t CREATE YEAR SECTION "<<endl;
	do {
		cout << "\t\t Created school year from: ";
		begin = Valid_Data(time);
		end = begin + 1;
		ss1 << begin; ss1 >> name1;
		ss2 << end; ss2 >> name2;
		path_temp = name1 + "-" + name2 + ".csv";
	} while (File_Exist(path_temp));
	const char* path = path_temp.c_str();
	fileInput= fopen(path,"a+");
	fclose(fileInput);
	Input_Year("Years.csv", path);
	cout << "\t\t School year created successfully" << endl;
	system("pause");
	return path;
}
void Year_Display()
{
	cout << "\t\t Year display function" << endl;
	cout << "\t\t Choose your option: " << endl;
}
//Process year task
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
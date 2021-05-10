#include "Class.h"

//Converting function
string Int_ToString(int n)
{
	stringstream ss; string s;
	ss << n; ss >> s;
	ss.str("");
	ss.clear();
	return s;
}
string ClassName_To_Path(string year_name,string class_name)
{
	return  ".\\Classes\\" + year_name.substr(0, 9) + "\\" + class_name;
}

//Choose kind of class creating
int Create_Type()
{
	cout << "\t\t CREATE CLASS SECTION " << endl;
	cout << "\t\t 1. Import classes from files" << endl;
	cout << "\t\t 2. Add single class" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(2);
}
//Put class path into list
void Input_Class(string year_name, string class_name)
{
	string year_path = ".\\Years\\" + year_name;
	cout << "\t\t Save class at " << year_path << endl;
	fstream f(year_path, ios::app | ios::out);
	f << class_name << endl;
	f.close();
}
//Delete directory
void Delete_Directory(string dir)
{
	dir = "rmdir /s /q " + dir;
	system(dir.c_str());
}

//Option 1

paths Import_Class(string file,string year_name)
{
	fstream f(file);
	paths list = Init_List();

	while (!f.eof())
	{
		string class_name;
		f >> class_name;

		//Check for duplicating
		if (Duplicated_Class(year_name, class_name)) continue;

		//Add class info to list of nodes
		path* node = Create_Node(class_name);
		Add_Last(list, node);
	}
	f.close();
	
	//Add and create
	path* move = list.head;
	while (move->next != nullptr)
	{
		//Add class path into year file
		Input_Class(year_name, move->info);
		//Create new class file in Classes directory
		string class_path = ".\\Classes\\" + year_name.substr(0, 9) + "\\" + move->info;
		f.open(class_path.c_str(),ios::out);
		f.close();
		move = move->next;
	}
	return list;
}
string Year_Selection()
{
	cout << "\t\t Which year do you want to modify ?" << endl;
	int limit = Years_Display();
	cout << "\t\t Select option: ";
	int choice = Valid_Data(limit);
	string year_name = "NA";
	fstream f("Years.csv", ios::in); int count = 1;
	while (!f.eof() && choice > 0)
	{
		f >> year_name;
		if (count++ == choice)
		{
			//Only create new directory of classes when year is selected
			Create_Directory(year_name);
			return year_name;
		}
	}
	f.close();
	system("cls");
	return year_name;
}
string Create_Directory(string year_name)
{
	string dir = ".\\Classes\\" + year_name.substr(0, 9) + "\\";
	cout << "\t\t Directory path: " << dir << endl;
	// Creating a directory
	if (_mkdir(dir.c_str()) == -1)
		cerr << "\t\t Error :  " << strerror(errno) << endl;

	else
		cout << "\t\t Directory created" << endl;
	return dir;
}
string File_Import()
{
	string file_path;
	bool check = true;
	do {
		//Receive file name from user
		cout << "\t\t Enter file name for importing: ";
		string name;
		cin.ignore();
		getline(cin, name, '\n');
		
		//Create file's path
		file_path = name + ".csv";
		cout << "\t\t Import file from: " << file_path << endl;
		check = File_Exist(file_path);
	} while (check == false);
	return file_path;

}
//Option 2

//Get code name for each department
//Check whether class is existed
bool Duplicated_Class(string year_name, string check)
{
	string path  = ClassName_To_Path(year_name, check);
	cout << "\t\t Check file at path: " << path << endl;
	if (File_Exist(path))
	{
		string year_path = ".\\Years\\" + year_name;
		fstream f(year_path, ios::in);
		while (!f.eof())
		{
			string read;
			f >> read;
			if (read == check)
			{
				return true;
			}
		}
	}
	return false;
}
string Department_Name(int depart,int system)
{
	string name;
	switch (depart)
	{
	case 1: {name= "CTT"; break; }
	case 2: {name= "DCH"; break; }
	case 3: {name= "DTV"; break; }
	case 4: {name= "HOH"; break; }
	case 5: {name= "KVL"; break; }
	case 6: {name= "KMT"; break; }
	case 7: {name= "SHH"; break; }
	case 8: {name= "TTH"; break; }
	default: {name= "VLH"; break; }
	}
	if (system == 2)
	{
		name = name + "_CLC";
	}
	return name;
	
}
string Create_Class_Single(string year_name, int time)
{
	
	string class_name, syntax, period = Int_ToString(time % 100);
	int n = 0;

	syntax = Department_Name(Department_Menu_Disp(),Training_System_Menu_Disp());
	bool check = true;

	do {
		cout << "\t\t Enter order of class: ";
		cin >> n;

		class_name = period + syntax + Int_ToString(n) + ".csv";
		check = Duplicated_Class(year_name, class_name);

	} while (n < 0 || n>5 || check == true);
	
	string class_path = ClassName_To_Path(year_name, class_name);
	fstream f(class_path, ios::out);
	f.close();

	cout << "\t\t File path: " << class_path << endl;
	cout << "\t\t Class created successfully" << endl;

	Input_Class(year_name, class_name);
	cout << "\t\t ";  system("pause"); system("cls");
	return class_path;
}

////Class Deleting//
void Class_Delete(string year_path,int quanti)
{
	cout << "\t\t Chosse class: ";
	int choice = Valid_Data(quanti);

	int i = 1;
	string class_path = ".\\Classes\\" + Path_ToYear(year_path).substr(0,9) + "\\";
	paths list = Init_List();
	fstream f(year_path, ios::in | ios::out);

	while (!f.eof())
	{
		string class_name;
		f >> class_name;
		path* node = Create_Node(class_name);
		Add_Last(list, node);
		
		class_path += class_name;
		if (i++ == choice)
		{
			remove(class_path.c_str());
			Remove_Info(list, class_name);
		}
	}
	f.close();
	remove(year_path.c_str());
	f.open(year_path.c_str(), ios::out);
	f.close();
	ReInput_fromList(year_path, list);
}
////Clear all classes//
void Class_Clear(string year_path)
{
	cout << "\t\t All classes will be deleted !!!!" << endl;
	cout << "\t\t Are you sure ???" << endl;
	cout << "\t\t Press 0 for accepting, 1 for not:  ";
	int n; cin >> n;
	if (n == 0)
	{
		fstream f(year_path, ios::in | ios::out);
		int i = 1;

		while (!f.eof()) {

			string class_name;
			f >> class_name;

			//Delete files
			string class_path = ".\\Classes\\" 
				+ Path_ToYear(year_path).substr(0, 9) 
				+ "\\"
				+ class_name;
			remove(class_path.c_str());

		}
		f.close();
		//Remake a new year's file
		remove(year_path.c_str());
		f.open(year_path.c_str(), ios::out);
		f.close();
		/*string dir = ".\\Classes\\"
			+ Path_ToYear(year_path).substr(0, 9);
		Delete_Directory(dir);*/
	}
}
////Classes displaying//
int Classes_Display(string year_path)
{
	if (File_Exist(year_path) == false)
	{
		return 0;
	}
	system("cls");
	cout << "\t\t CREATED CLASS: " << endl;
	fstream f(year_path, ios::in); int i = 1;

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
	return i-1;
}

//Process class task
bool Class_Proc_Active(int option,int time)
{
	string year_name = Year_Selection();
	string year_path = ".\\Years\\" + year_name;
	Classes_Display(year_path);

	if (option == 1)
	{
		if (year_name != "NA")
		{
			int choice = Create_Type();
			if (choice == 1) {

				string path = File_Import();
				Import_Class(path, year_name);

			}
			else {
				Create_Class_Single(year_name, time);
			}
		}
		return true;
	}
	else if (option == 2)
	{
		int quanti = Classes_Display(year_path);
		cout << "\t\t This year has " << quanti << " class(es)" << endl;
		Class_Delete(year_path,quanti);
		system("cls");
		return true;
	}
	else if (option == 3)
	{
		Class_Clear(year_path);
		system("cls");
		return true;
	}
	else if(option ==4)
	{
		return false;
	}

}

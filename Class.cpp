#include"Menu.h"
#include"Year.h"
#include"Class.h"
#include "Node Process.h"

//Choose kind of class creating
int Create_Type()
{
	cout << "\t\t CREATE CLASS SECTION " << endl;
	cout << "\t\t 1. Import classes from files" << endl;
	cout << "\t\t 2. Add single class" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(2);
}
//Check whether class is existed
bool Check_Class(string classes, string name)
{
	string path = ".\\Classes\\" + Path_To_Directory(classes) + "\\" + name + ".csv";
	cout << "\t\t Check file at path: " << path << endl;
	if (File_Exist(path))
		return true;
	return false;
}
//Put class path into list
void Input_Class(string store, string path)
{
	cout << "\t\t Save class at" << store << endl;
	fstream f(store, ios::app | ios::out);
	f << path << endl;
	f.close();
}

//Option 1

yrs Import_Class(string classes, string file)
{
	fstream f(file);
	yrs list = Init_List();

	while (!f.eof())
	{
		string read;
		f >> read;
		cout << read << endl;
		yr* node = Init_Node(read);
		Add_Last(list, node);
	}
	f.close();

	cout << "\t\t Saved to node" << endl;
	Output_List(list);
	system("pause");
	/*yr* move = list.head;
	while (move->next != nullptr)
	{
		
		Input_Class(classes, move->path);
		
		string path = ".\\Classes\\" + Path_To_Directory(classes) + "\\" + move->path;
		FILE* f = fopen(path.c_str(), "a+");
		fclose(f);

		move = move->next;
	}*/
	return list;
}

//Option 2

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
//Converting function
string Convert_Char(char*ch)
{
	stringstream ss; string s;
	ss << ch; ss >> s;
	return s;
}
string Convert_Int(int n)
{
	stringstream ss; string s;
	ss << n; ss >> s;
	ss.str("");
	ss.clear();
	return s;
}
string Code_to_Name(string period, string code, string order)
{
	return period + code + order + ".csv";
}
string Path_To_Directory(string classes)
{
	return ParsePath(classes).substr(0, 9);
	//If want convert from path to  name,just add ".csv" at the last of this function
} 
string Name_To_Path(string period,string code,string order,string classes)
{
	string path = ".\\Classes\\" + Path_To_Directory(classes) + "\\";
	path = path + Code_to_Name(code, period, order);
	return path;
}

string Create_Class_Single(string classes, int time)
{
	FILE* fileInput;
	string code, period = Convert_Int(time % 100);
	int n = 0;

	code = Department_Name(Department_Menu_Disp());
	bool check = true;

	do {
		cout << "\t\t Enter order of class: ";
		cin >> n;

		string temp = period + code + Convert_Int(n);
		check = Check_Class(classes, temp);

	} while (n < 0 || n>5 || check == true);
	
	
	string path = Name_To_Path(period,code,Convert_Int(n),classes);
	fileInput = fopen(path.c_str(), "a+");
	fclose(fileInput);

	cout << "\t\t File path: " << path << endl;
	cout << "\t\t Class created successfully" << endl;

	Input_Class(classes, ParsePath(path));
	cout << "\t\t ";  system("pause");
	return path;
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
		int choice  = Create_Type();
		if (choice == 2) {
			Create_Class_Single(classes, 2021);
		}
		else {
			string path;
			bool check = true;
			do {
				
				cout << "\t\t Enter file name for importing: "; 
				string name;
				getline(cin, name,'\n');
				cin.ignore(32767,'\n');
				path = name + ".csv";
				cout << "\t\t Import file from: " << path << endl;

				check = File_Exist(path);
			} while (check==false);
			
			Import_Class(classes, path);
		}
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

#include "Menu.h"
#include "Year.h"
#include "Class.h"
#include "File.h"
#include "Convert.h"
#include "Node Process.h"
//Kiểm tra lớp có bị trùng trong danh sách của năm hay không.
//Param: tên năm và tên lớp cần kiểm tra
//Return: True nếu trùng, False nếu ngược lại
bool Duplicated_Class(string year_name, string check_class)
{
	//Create folder path automatically
	string pre_folder = ".\\Classes\\" + year_name + "\\";
	string check_path = Make_Path(pre_folder, check_class);
	cout << "\t\t Check file at path: " << check_path << endl;
	if (File_Exist(check_path))
	{
		return true;
	}
	return false;
}
//Hàm nhập hàng loạt lớp từ file
//Param: Đường dẫn file cần nhập (nằm trong thư mục Classes) và tên năm
//Return: Danh sách liên kết chứa các tên lớp
names Class_Import(string import_file,string year_name)
{
	fstream f(import_file);
	names list = Init_List();

	while (!f.eof())
	{
		string class_name;
		f >> class_name;

		//Kiểm tra trùng lặp
		if (Duplicated_Class(year_name, class_name)) continue;

		//Thêm các tên lớp vào danh sách liên kết
		name* node = Create_Node(class_name);
		Add_Last(list, node);
	}
	f.close();
	
	//Thêm các tên lớp từ danh sách liên kết sang file CSV của năm và tạo file lớp
	name* move = list.head;
	while (move->next != nullptr)
	{
		//Thêm tên lớp vào file CSV của năm
		string year_path = ".\\Years\\" + Extension(year_name, 1);
		Save_ToCSV(year_path, move->info);
		//Tạo một file lớp mới
		string class_path = ".\\Classes\\" + year_name + "\\" + Extension(move->info,1);
		File_Create(class_path);
		move = move->next;
	}
	return list;
}
//Hàm xử lý tên các khoa trong trường
//Param: số thứ tự khoa, số thứ tự của hệ đào tạo
//Return: Mã Khoa - Hệ đào tạo 
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
//Hàm tạo tên lớp
//Param: tên năm
//Return: một chuỗi có tên lớp hoàn chỉnh
string Make_ClassName(string year_name)
{
	//Tạo số niên khóa
	int first_year = Year_ToInt(year_name);
	string class_name, department, period = Int_ToString(first_year % 100);
	int n = 0;
	//Tạo mã khoa - hệ đào tạo
	department = Department_Name(Department_Menu_Disp(), Training_System_Menu_Disp());
	bool check = true;
	//Nhập số thứ tự lớp (1 đến 5)
	do {
		cout << "\t\t Enter order of class: ";
		cin >> n;

		class_name = period + department + Int_ToString(n);
		check = Duplicated_Class(year_name, class_name);

	} while (n < 0 || n>5 || check == true);
	return class_name;

}
//Tạo một lớp thủ công
//Param: tên năm
//Return: đường dẫn đến file lớp mới tạo
string Class_Create_Single(string year_name)
{
	string class_name = Make_ClassName(year_name);
	string pre_folder = ".\\Classes\\" + year_name + "\\";
	string class_path = Make_Path(pre_folder, class_name);
	File_Create(class_path);

	cout << "\t\t File path: " << class_path << endl;
	cout << "\t\t Class created successfully" << endl;

	//Save class into year's file.
	string year_path = ".\\Years\\" + Extension(year_name,1);
	Save_ToCSV(year_path, class_name);
	cout << "\t\t ";  system("pause");
	return class_path;
}
//Xóa một lớp
//Param: đường dẫn của file năm và số lượng lớp hiện có
void Class_Delete(string year_path,int quanti)
{
	//Chọn lớp cần xóa
	cout << "\t\t Choose class: ";
	int choice = Valid_Data(quanti);

	int i = 1;
	string class_path = ".\\Classes\\" + Path_ToName(year_path) + "\\";
	names list = Init_List();
	fstream f(year_path, ios::in | ios::out);
	//Duyệt qua và kiếm lớp cần xóa
	while (!f.eof())
	{
		string read;
		f >> read;
		//Lưu vào danh sách liên kết
		if (i++ != choice) //Nếu không phải lớp cần xóa thì cho vào LList
		{
			name* node = Create_Node(read);
			Add_Last(list, node);
		}
		else //Nếu là lớp cần xóa thì xóa thư mục của lớp đó
		{
			class_path += Extension(read, 1);
			remove(class_path.c_str());
		}
	}
	f.close();
	//Tạo file lớp mới và truyền dữ liệu từ LList vào lại
	File_Clear(year_path);
	ReInput_fromList(year_path, list);
}
//Xóa tất cả các lớp
//Param: đường dẫn tới file năm
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

			string read;
			f >> read;

			//Xóa thư mục năm chứa nhiều lớp
			string class_path = ".\\Classes\\"
				+ Path_ToName(year_path)
				+ "\\"
				+ Extension(read,1);
			remove(class_path.c_str());
		}
		f.close();
		//Tạo lại một file năm mới
		File_Clear(year_path);
	}
}
//Hiển thị các lớp
//Param: đường dẫn đến file năm
//Return: Số lượng năm hiện có
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
//Xử lý và điều hướng các hàm tính năng của lớp
//Param: tên năm, các lựa chọn tính năng
bool Class_Proc_Active(string year_name,int option)
{
	//Khởi tạo các đường dẫn & thư mục cần thiết
	string year_path = ".\\Years\\" + Extension(year_name,1);
	string folder = ".\\Classes\\";
	if (option == 1)
	{
		//Duyệt và tạo ra thư mục con của Classes chứa các lớp
		Browse_and_CreateFolder("Years.csv", folder,year_name);
		if (year_name != "")
		{
			//Lựa chọn cách tạo lớp
			int choice = Class_Create_Mod_Menu();
			//Option 1: Nhập từ file
			if (choice == 1) {

				string import_path = File_Import(folder);
				Class_Import(import_path, year_name);
			}
			//Option 2: Thủ công
			else {
				Class_Create_Single(year_name);
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
		system("cls");
		return false;
	}
	else
	{
		system("cls");
		return true;
	}

}

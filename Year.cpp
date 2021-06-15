#include "Menu.h"
#include "Year.h"
#include "Class.h"
#include "Convert.h"
#include "File.h"
#include "Node Process.h"
//Param: Năm bắt đầu và năm kết thúc.
//Return: Tên của năm (string)
string Make_YearName(int begin, int end)
{
	return  Int_ToString(begin) + "-" + Int_ToString(end);
}
//Hàm tạo năm
//Param: Năm lớn nhất có thể tạo (giới hạn)
void Year_Create(int year)
{
	int begin, end;
	string year_path, year_name, pre_folder = ".\\Years\\";

	//Tạo ra cái tên của năm, đường dẫn của năm.
	cout << "\t\t CREATE YEAR SECTION " << endl;
	do {
		cout << "\t\t Created school year from: ";
		begin = Valid_Data(year);
		end = begin + 1;
		year_name = Make_YearName(begin, end);
		year_path = Make_Path(pre_folder,year_name);
		if(begin<2002)  {cout<<"\t\t New School Year must be after 2002"<<endl;}
	} while (File_Exist(year_path)== true || begin <2002);
	//Năm được tạo không được bé hơn 2002

	//Tạo ra file năm mới
	File_Create(year_path);
	//Lưu các tên năm vào file Years.csv
	Save_ToCSV("Years.csv", year_name.c_str());

	cout << "\t\t School year created successfully" << endl;
	cout << "\t\t "; system("pause");
}
//Lấy và lưu thông tin cần thiết để xóa một phần tử nào đó
//Param: 
//pre_folder: Thư mục chứa file cần xóa
//store: File cần xóa phần tử, lưu các giá trị là tên các phần tử
//choice: Số thứ tự của phần tử cần xóa
//name: Tên của phần tử sẽ xóa
//path: Đường dẫn của phần tử sẽ xóa
//Return: 
//Một danh sách liên kết chứa tên của các phần tử còn lại
names Deleted_Info(string pre_folder, string store,int choice, string &year_name, string &year_path)
{
	names list = Init_List();
	fstream f(store, ios::in | ios::out);
	int i = 1;

	while (!f.eof()) {
		//Đọc các tên phần tử từ file csv ra biến read
		string read;
		f >> read;
		//Thêm các tên phần tử vào danh sách liên kết
		if (i++ != choice) {
			name* node = Create_Node(read);
			Add_Last(list, node);
		}
		else {
			year_name = read;
			year_path = Make_Path(pre_folder, year_name);
		}
	}
	f.close();
	return list;
}
//Xóa một năm
//Param: Số lượng phần tử tối đa có thể xóa của năm
void Year_Delete(int quanti)
{
	cout << "\t\t Choose option: ";
	int choice = Valid_Data(quanti);

	string years_path = "Years.csv", pre_folder = ".\\Years\\";
	string year_path, year_name;
	names list = Init_List();

	//Lưu thông tin để xóa
	list = Deleted_Info(pre_folder,years_path,choice,year_name,year_path);
	//Xóa file năm
	remove(year_path.c_str());
	//Xóa file Years.csv cũ và tạo file mới
	File_Clear(years_path);
	//Sao chép tên năm từ list vào file Years.csv
	ReInput_fromList(years_path, list);
	//Xóa thư mục năm trong thư mục Classes
	string classes_folder = ".\\Classes\\"
		+ year_name + "\\"; //Cần có ký hiệu cuối cùng này để hoàn thành đường dẫn thư mục
	Directory_Delete(classes_folder);
	//Directory_Create(".\\Classes\\");
}
//Xóa toàn bộ năm
void Year_Clear()
{
	cout << "\t\t All years will be deleted !!!!" << endl;
	cout << "\t\t Are you sure ???" << endl;
	cout << "\t\t Press 0 for accepting, 1 for not:  ";
	int n; cin >> n;

	string year_name, year_path;
	if (n == 0)
	{
		fstream f("Years.csv", ios::in | ios::out);
		int i = 1;

		while (!f.eof()) {
			
			string read; f >> read;
			//Delete files
			year_path = Make_Path(".\\Years\\", year_name);
			remove(year_path.c_str());
			//Delete class folder
			year_name = read;
			string classes_folder = ".\\Classes\\"
				+ year_name + "\\"; //Have to use this syntax to accomplish folder path
			Directory_Delete(classes_folder);
			Directory_Create(".\\Classes\\");
		}
		f.close();
		//Create a new "Years.csv"
		File_Clear("Years.csv");
	}
}
//Hiển thị năm
//Return: Số lượng năm hiện có
int Years_Display()
{
	system("cls");
	File_YearSort("Years.csv");
	cout << "\t\t CREATED YEARS: " << endl;
	cout << "\t\t 0. Back" << endl;
	fstream f("Years.csv", ios::in);
	int i = 1;

	//Reading Years information from "Years.csv"
	while (!f.eof()) {
		string read;
		f >> read;
		if (read != "") {
			cout << "\t\t " << i++ << ". " << read << endl;
		}
	}
	f.close();
	return i-1;
}
//Chọn năm
//Return: Tên của năm đã chọn
string Year_Selection()
{
	int limit = Years_Display();
	cout << "\t\t Which year do you want to modify ?" << endl;
	cout << "\t\t Select option: ";
	int choice = Valid_Data(limit);

	fstream f("Years.csv", ios::in | ios::out);
	string year_name;
	int i = 1;

	while (!f.eof()) {
		//Read year file's name from "Years.csv"
		string read;
		f >> read;
		//Add year file's name into list of nodes
		if (i++ == choice)
		{
			year_name = read;
			return year_name;
		}
	}
	f.close();
	if (choice == 0)
	{
		return "!";//Thoát ra ngoài luôn
	}
	return "";//Có thể tiếp tục vòng lặp
}
//Xử lý và điều hướng các hàm tính năng của năm
//Param: lựa chọn tính năng và năm giới hạn
bool Year_Proc(int option, int limited_year)
{
	if (option == 1)
	{
		Year_Create(limited_year);
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
		Year_Clear();
		system("cls");
		return true;
	}
	else
	{
		system("cls");
		return false;
	}
}


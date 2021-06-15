#include "File.h"
#include "Convert.h"
#include "Node Process.h"
//Kiểm tra sự tồn tại của file
//Param: đường dẫn chứa file
//Return: False nếu file không tồn tại
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
	fileInput.close();
}
//Tạo file mới
//Param: đường dẫn của file cần tạo
void File_Create(string file_path) 
{
	FILE* fileInput = fopen(file_path.c_str(), "a+");
	fclose(fileInput);
}
//Làm rỗng file
//Đường dẫn đến file
void File_Clear(string file_path)
{
	remove(file_path.c_str());
	fstream f(file_path, ios::out);
	f.close();
}
//Sắp xếp file (dùng cho năm)
//Đường dẫn đến file
void File_YearSort(string file_path)
{
	fstream f(file_path, ios::in | ios::out);
	names list = Init_List();

	while (!f.eof())
	{
		string read;
		f >> read;
		//Add info into list of nodes
		name* node = Create_Node(read);
		Add_Last(list, node);
	}
	f.close();
	SortAscen_YearList(list);
	//Remake a new source file
	remove(file_path.c_str());
	f.open(file_path.c_str(), ios::out);
	f.close();
	ReInput_fromList(file_path, list);
}
//Lưu các name từ file sang danh sách liên kết chứa name
//Đường dẫn chứa file
//Danh sách liên kết chứa các tên
names File_to_NameList(string path)
{
	names l = Init_List();
	ifstream f;
	f.open(path);
	while (!f.eof())
	{
		string f1;
		getline(f, f1);
		name* p = Create_Node(f1);
		Add_Last(l, p);
	}
	f.close();
	return l;
}

//Lưu tên vào file lưu giữ
//Param: File lưu giữ, file cần lưu
void Save_ToCSV(string store, string name)
{
	fstream f(store, ios::app | ios::out);
	f << name << endl;
	f.close();
}
//Lưu tên vào file lưu giữ tại 1 hàng nào đó, lưu vào cột tiếp theo
//store: file lưu giữ
//line_name: tên của hàng
//newname: tên mới cần lưu vào hàng
void Save_ToCSVLine(string store,string line_name, string newname)
{
	cout << newname << endl;
	fstream f(store, ios::in | ios::out);
	names list = Init_List();
	while (!f.eof())
	{
		string read;
		f >> read;
		cout << read << endl;
		if (read == line_name)
		{
			read += ("," + newname);
		}
		name* node = Create_Node(read);
		Add_Last(list, node);
	}
	f.close();
	ReInput_fromList(store, list);
}
//Xóa một thư mục
//Param: đường dẫn thư mục
void Directory_Delete(string dir)
{
	dir = "rmdir /s /q " + dir;
	system(dir.c_str());
}
//Tạo một thư mục mới
//Đường dẫn thư mục
void Directory_Create(string dir)
{
	cout << "\t\t Directory path: " << dir << endl;
	// Creating a directory
	if (_mkdir(dir.c_str()) == -1)
		cerr << "\t\t Error :  " << strerror(errno) << endl;

	else
		cout << "\t\t Directory created" << endl;
}
//Dò tìm và tạo một thư mục mới
//Tham số: "store" là đường dẫn file lưu thông tin các file khác.
//"folder" là thư mục cần dò tạo.
//"name" là tên thư mục cần tạo.
string Browse_and_CreateFolder(string store, string folder,string name)
{
	fstream f(store, ios::in);
	while (!f.eof())
	{
		string read;
		f >> read;
		if (read == name)
		{
			//Only create new directory of classes when year is selected
			string dir = folder + read + "\\";
			Directory_Create(dir);
			return read;
		}
	}
	f.close();
	return "!";
}
//Kiểm tra tên có trong file hay chưa
//store: file cần kiểm tra, name: tên cần kiểm tra
//True nếu đã tồn tại, ngược lại là False
bool Name_InFile(string store, string name)
{
	fstream f;
	f.open(store.c_str(), ios::in);

	while (!f.eof())
	{
		string read;
		f >> read;
		if (read == name)
		{
			return true;
			break;
		}
	}
	f.close();
	return false;
}
//Nhập file 
//Thư mục chứa file
//Đường dẫn đến file
string File_Import(string folder)
{
	string file_path;
	bool check = true;
	do {
		//Nhập tên file cần import
		cout << "\t\t Enter file name for importing: ";
		string name;
		cin.ignore();
		cin >> name;
		//Tạo đường dẫn file import
		file_path = folder + Extension(name, 1);
		cout << "\t\t Import file from: " << file_path << endl;
		check = File_Exist(file_path);
	} while (check == false);
	cout << "\t\t "; system("pause");
	return file_path;
}
//Đếm số dòng trong file
//Param: đường dẫn đến file
//Số dòng trong file
int Count_line(string path)
{
	ifstream f;
	f.open(path);
	int c = 0;
	while (!f.eof())
	{
		string s1 = "";
		getline(f,s1);
		c++;
	}
	f.close();
	return c - 1;
}





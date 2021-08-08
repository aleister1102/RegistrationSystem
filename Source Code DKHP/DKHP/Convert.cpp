#include "Convert.h"
//Thêm phần mở rộng (.csv) vào tên file hoặc cắt nó đi
//Param: một tên/tên file cần thêm/cắt, một option chọn loại hành động
//Return: kết quả của chuỗi sau khi thêm/cắt
string Extension(string name, int option)
{
	//Nếu option là 1: thêm phần đuôi ".csv"
	if (option == 1) {
		return name + ".csv";
	}
	//Nếu option là 2: cắt phần đuôi
	else {
		int pos = name.find_last_of(".", strlen(name.c_str()));
		return name.substr(0, pos);
	}
}
//Tạo ra một đường dẫn từ tên file(ko có đuôi ".csv") và đường dẫn thư mục chứa nó
//Param: một đường dẫn thư mục, một tên của file
//Return: Đường dẫn hoàn chỉnh
string Make_Path(string pre_folder, string file_name)
{
	return  pre_folder + Extension(file_name, 1);
}
//Cắt ra một tên (không có đuôi ".csv") từ một đường dẫn hoàn chỉnh
//Param: một đường dẫn hoàn chỉnh
//Return: tên của file (không có extension)
string Path_ToName(string path)
{
	int pos = path.find_last_of("\\", strlen(path.c_str()));
	return Extension(path.substr(size_t(pos) + 1), 2);
}
//Chuyển từ kiểu Int sang kiểu String
//Param: Số cần chuyển
//Return: Kiểu string sau khi chuyển
string Int_ToString(int number)
{
	stringstream ss; string s;
	ss << number; ss >> s;
	ss.str(""); ss.clear();
	return s;
}
//Chuyển từ một tên năm sang kiểu int (lấy năm đầu tiên)(VD: 2002-2003 thì lấy 2002)
//Param: tên năm
//Return: Dạng số int của năm đầu tiên trong tên năm
int Year_ToInt(string year_name)
{
	int pos = year_name.find_last_of("-", strlen(year_name.c_str()));
	string first_year = year_name.substr(0, pos);
	stringstream ss; int number;
	ss << first_year; ss >> number;
	return number;
}




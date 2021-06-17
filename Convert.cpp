#include "Header/Convert.h"
#include "Header/File.h"
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
//Chuyển từ kiểu String sang kiểu Int
//Chuỗi cần chuyển
//Giá trị int sau khi chuyển
int String_ToInt(string s)
{
	stringstream ss;int number;
	ss<<s;ss>>number;
	ss.str("");ss.clear();
	return number;
}
//Chuyển từ một tên năm sang kiểu int (lấy năm đầu tiên)(VD: 2002-2003 thì lấy 2002)
//Param: tên năm
//Return: Dạng số int của năm đầu tiên trong tên năm
int Year_ToInt(string year_name)
{
	int pos = year_name.find_last_of("-", strlen(year_name.c_str()));
	string first_year = year_name.substr(0, pos);
	return String_ToInt(first_year);
}
//Chuyển từ file chứa string sang mảng string
//Đường dẫn file
//Mảng chứa string
string* File_toStringArray(string path)
{
	int n = Count_line(path);
	fstream file;
	file.open(path);
	string* s = new string[n + 1];
	int i = 0;
	while (!file.eof())
	{
		string s1;
		getline(file, s1);
		s[i++] = s1;
	}
	file.close();
	return s;
}
//Chuyển đổi từ ngày tháng sang chuỗi ngày tháng
//Kiểu dữ liệu ngày tháng năm
//Chuỗi ngày tháng năm
string Date_toString(date dmy)
{
	return (Int_ToString(dmy.day)+ "/"
	+Int_ToString(dmy.month)+"/"
	+Int_ToString(dmy.year));
}
date String_ToDate(string dmy)
{
	date result;
	int length = dmy.length();
	int i=1;
	string arr[3];
	while(i<2)
	{
		int pos = dmy.find_first_of("/",0);
		string temp = dmy.substr(0,pos);
		arr[i++]= temp;
		dmy = dmy.substr(pos+1,length);
	}
	result.day=String_ToInt(arr[0]);
	result.month=String_ToInt(arr[1]);
	result.year=String_ToInt(arr[2]);
	return result;
}
//Chuyển đổi từ chuỗi thông tin học sinh sang kiểu học sinh
//Chuỗi thông tin, mảng lưu thông tin nếu cần dùng kiểu mảng
//Thông tin học sinh dạng struct
Student String_ToStudent(string info,string arr[8])
{
    Student sv;
	int length = info.length(); 
	int i = 0;

    while (i <=7)
    {
		
        int pos = info.find_first_of(",", 0);
        string temp = info.substr(0,pos);
		if(i<7)
		{
			info = info.substr(pos + 1, length);
			arr[i++] = temp;
		}
		else{
			arr[i++]=info;
		}
    }
	
	sv.number = String_ToInt(arr[0]);
	sv.id = String_ToInt(arr[1]);
	sv.name=arr[2];
	sv.gender=arr[3];
	sv.faculty=arr[4];
	sv.birthdate =arr[5];
	sv.socialID=String_ToInt(arr[6]);
	sv.user.username=arr[1];
	sv.user.password=arr[7];
	return sv;
}


#include "Header/Semester.h"
#include "Header/Menu.h"
#include "Header/Year.h"
#include "Header/Class.h"
#include "Header/File.h"
#include "Header/Convert.h"
#include "Header/Node Process.h"

//Lấy tên của season từ dữ liệu thời gian hiện tại
//Dữ liệu thời gian (tháng)
//Chuỗi tên season
string Season_Name(date dmy)	
{
	if(dmy.month>=9 &&dmy.month<=12){
		return "-Autumn";
	}
	else if(dmy.month>=5 && dmy.month<7){
		return "-Fall";
	}
	return "-Summer";
}
//Tạo học kỳ
//Năm hiện tại cần tạo học kỳ
void Create_Semester(string year_name,date dmy)
{
	cout<<"\t\t Current time: "<<dmy.month<<endl;
	string pre_folder = ".\\Semesters\\" + year_name + "\\";
	string season = Season_Name(dmy);
	string semester_path = pre_folder + Extension(year_name + season,1);
	string semesters = ".\\Semesters\\Semesters.csv";
	
	if(!File_Exist(semester_path))
	{
		File_Create(semester_path);
	}
	if(!Name_InFile(semesters,year_name)){
		Save_ToCSV(semesters,year_name);
	}
	cout<<"\t\t ";system("pause");
}
//Hàm chọn semester để chỉnh sửa
//Số semester hiện có trong năm, năm hiện tại
//Đường dẫn đến file semester cần chỉnh sửa
string Semester_Selection(int limited_semester,string year_name)
{
	cout<<"\t\t Choose semester to modify: ";
	int option  = Valid_Data(limited_semester);
	string pre_folder = ".\\Semesters\\" + year_name + "\\";
	string seasons[3] = { "-Autumn","-Fall","-Summer" };
	int count=0;

	for(int i =1;i<=3;i++)
	{
		string semester_name = Extension(year_name + seasons[i-1],1);
		string semester_path = pre_folder + semester_name;
		if(File_Exist(semester_path))
		{
			count+=1;
			if(count==option)
			{
				return semester_path;
			}
		}
	}
}
//Xóa một học kỳ
//Năm hiện tại cần xóa học kỳ
//True nếu cần dùng lại hàm, false nếu không
bool Semester_Delete(int limited_semester,string year_name)
{
	if(limited_semester <1) return false;
	string semester_path = Semester_Selection(limited_semester,year_name);
	remove(semester_path.c_str());

	string pre_folder = ".\\Semesters\\" + year_name + "\\";
	string seasons[3] = { "-Autumn","-Fall","-Summer" };
	for(int i=1;i<=3;i++)
	{
		string semester_name = Extension(year_name + seasons[i-1],1);
		string semester_path = pre_folder + semester_name;
		if(File_Exist(semester_path)) return true;
	}

	Directory_Delete(pre_folder);
	return false;
}
//Hiển thị semester hiện có trong năm
//Năm hiện tại
//Số semester đếm được
int Semesters_Display(string year_name)
{
	system("cls");
	string pre_folder = ".\\Semesters\\" + year_name + "\\";
	string seasons[3] = { "-Autumn","-Fall","-Summer" };
	string semesters =".\\Semesters\\Semesters.csv";
	int count=1;
	
	cout<<"\t\t CREATED SEMESTER OF "<<year_name<<endl;
	for(int i=1;i<=3;i++)
	{
		string semester_name = year_name+seasons[i-1];
		string semester_path = pre_folder+Extension(semester_name,1);
		if(File_Exist(semester_path))
		{
			cout<<"\t\t "<<count++<<". "<<semester_name<<endl;
		}
	}
	cout<<"\t\t ";system("pause");	
	return count;
}
//Xử lý các tính năng của semeste
//Sự lựa chọn tính năng, năm hiện tại, dữ liệu thời gian hiện tại
//True nếu cần dùng tiếp, false nếu ngược lại
bool Semester_Proc(int option,string year_name,date dmy)
{
	if (option == 1)
	{
		string run = Browse_and_CreateFolder("Years.csv", ".\\Semesters\\", year_name);
		if (run == "!") return true;
		Create_Semester(year_name,dmy);
		system("cls");
		return true;
	}
	else if (option == 2)
	{
		bool run = true;
		while(run){
		int limited_semester = Semesters_Display(year_name);
		run  = Semester_Delete(limited_semester,year_name);
		system("cls");
		}
		return true;
		
	}
	else if (option == 3)
	{
		Semesters_Display(year_name);
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
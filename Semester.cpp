#include "Header\Semester.h"
#include "Header\Menu.h"
#include "Header\Year.h"
#include "Header\Class.h"
#include "Header\File.h"
#include "Header\Convert.h"
#include "Header\Node Process.h"

//*Xem ngày tháng của học kỳ
//@param time Chuỗi ngày tháng
void View_Semester_Time(string time) 
{
	int pos = time.find_first_of(",",0);
	cout<<"\t\t Begining time: "<<time.substr(0,pos)<<endl;
	cout<<"\t\t Ending time: "<<time.substr(pos+1,time.size())<<endl;
}
//*Xem ngày tháng đăng ký học phần
//@param time Chuỗi ngày tháng
void View_Registration_Time(string time) 
{
	int pos = time.find_first_of(",",0);
	cout<<"\t\t Opening time: "<<time.substr(0,pos)<<endl;
	cout<<"\t\t Closing time: "<<time.substr(pos+1,time.size())<<endl;
}
//*Lấy tên của season từ dữ liệu thời gian hiện tại
//@param dmy Dữ liệu thời gian (tháng)
//@return Chuỗi tên season
string Season_Name(date dmy)	
{
	if(dmy.month>=9 &&dmy.month<=12){
		return "-Autumn";
	}
	else if(dmy.month>=1 && dmy.month<=4){
		return "-Spring";
	}
	return "-Summer";
}
//*Tạo ra ngày tháng của semester và ngày tháng ĐKHP 
//*và ghi vào file semester (dòng đầu của file semester mới tạo)
//@param year_name Năm học hiện tại 
//@param semester_suffix Hậu tố season của semester
//@param semester_path Đường dẫn đến file semester
void Semester_Time_Create(string year_name, string semester_suffix, string semester_path)
{
	int start_year = Year_ToInt(year_name);
	date semester_start,semester_end;
	date registration_start,registration_end;
	ofstream f(semester_path,ios::out);
	if(semester_suffix == "-Autumn")
	{
		semester_start = {15,9,start_year};
		semester_end = {15,12,start_year};
		registration_start = {1,9,start_year};
		registration_end = {10,9,start_year};
	}
	else if(semester_suffix == "-Summer")
	{
		semester_start={1,5,start_year+1};
		semester_end={31,7,start_year+1};
		registration_start={16,4,start_year+1};
		registration_end={26,4,start_year+1};
	}
	else{
		semester_start={1,1,start_year+1};
		semester_end={15,4,start_year+1};
		registration_start={16,12,start_year};
		registration_end={26,12,start_year};
	}
	string semester_time = Date_toString(semester_start)+","+ Date_toString(semester_end);
	string registration_time = Date_toString(registration_start)+","+Date_toString(registration_end);
	f<<semester_time<<endl;
	f<<registration_time<<endl;
	f.close();
}
//*Tạo học kỳ
//@param year_name Năm hiện tại cần tạo học kỳ
//@param dmy Thời gian hiện tại
void Semester_Create(string year_name, date dmy)
{
	cout<<"\t\t Current month: "<<dmy.month<<endl;
	//Tạo tên của học kỳ dựa vào thời gian hiện tại
	string season = Season_Name(dmy);
	string semester_folder = ".\\Semesters\\" + year_name + "\\";
	string semester_path = semester_folder + Extension(year_name + season,1);
	//Loại trừ trường hợp semester đã tồn tại
	if(File_Exist(semester_path))
	{
		cout<<"\t\t Semester is existed!"<<endl;
		cout<<"\t\t ";system("pause");
		return;
	}
	//Nếu không thì tạo file semester
	else File_Create(semester_path);
	//Tạo các thời gian liên quan cho semester
	Semester_Time_Create(year_name,season,semester_path);
	cout<<"\t\t ";system("pause");
}
//*Xóa một học kỳ
//@param limited_semester Số học kỳ giới hạn
//@param year_name Năm hiện tại cần xóa học kỳ
//@return True nếu cần dùng lại hàm, false nếu không
bool Semester_Delete(string year_name)
{
	//Chọn học kỳ cần xóa
	string semester_path = Semester_Select(year_name);
	if(semester_path=="OUT") return false;
	remove(semester_path.c_str());
	//Kiểm tra xem nếu đã xóa hết học kỳ của năm thì xóa luôn thư mục
	string pre_folder = ".\\Semesters\\" + year_name + "\\";
	string seasons[3] = { "-Autumn","-Spring","-Summer" };
	for(int i=1;i<=3;i++)
	{
		string semester_name = Extension(year_name + seasons[i-1],1);
		string semester_path = pre_folder + semester_name;
		if(File_Exist(semester_path)) return true;
	}
	Directory_Delete(pre_folder);
	return true;
}
//*Hiển thị semester hiện có trong năm
//@param year_name Năm hiện tại
//@return Số semester đếm được
int Semester_Display(string year_name)
{
	system("cls");
	string semester_folder = ".\\Semesters\\" + year_name + "\\";
	string seasons[3] = { "-Autumn","-Spring","-Summer" };
	int count=0;
	bool check=false;
	
	cout<<"\t\t CREATED SEMESTER OF "<<year_name<<endl;
	cout<<"\t\t 0. Back"<<endl;
	for(int i=1;i<=3;i++)
	{
		//Tạo tên và đường dẫn để kiểm tra sự tồn tại của học kỳ
		string semester_name = year_name+seasons[i-1];
		string semester_path = semester_folder+Extension(semester_name,1);
		if(File_Exist(semester_path))
		{
			//Nếu tồn tại thì xuất ra
			cout<<"\t\t "<<++count<<". "<<semester_name<<endl;
			check=true;
		}
	}
	if(check!=true)
	{
		cout<<"\t\t Can not find any semester"<<endl;
	}
	return count;
}
//*Hàm chọn semester để thao tác
//@param limited_semester Số semester hiện có trong năm @param year_name năm hiện tại
//@return Đường dẫn semester hoặc "OUT" (nếu không có sem nào hoặc muốn thoát ra)
string Semester_Select(string year_name)
{
	//Hiển thị semester
	int limited_semester = Semester_Display(year_name);
	if(limited_semester==0) return "OUT";
	//Chọn lựa semester
	cout<<"\t\t Choose semester to modify: ";
	int option  = Valid_Data(limited_semester);
	if(option <1) return "OUT";

	string semester_folder = ".\\Semesters\\" + year_name + "\\";
	string seasons[3] = { "-Autumn","-Spring","-Summer" };
	int count=0;
	
	for(int i =1;i<=3;i++)
	{
		//Tạo đường dẫn tới semester và lấy đường dẫn của nó
		string semester_name = Extension(year_name + seasons[i-1],1);
		string semester_path = semester_folder + semester_name;
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
//*Xử lý các tính năng của semester	
//@param year_name Năm hiện tại @param dmy Dữ liệu thời gian hiện tại
//@param option Sự lựa chọn tính năng 
//@return True nếu cần dùng tiếp, false nếu ngược lại
bool Semester_Proc(string year_name, date dmy, int option)
{
	//!Năm học này là năm học hiện tại (không phải được chọn)
	string year_path = Make_Path(".\\Years\\",year_name);
	if(File_Exist(year_path)==false && option !=3)
	{
		cout<<"\t\t This year was not created"<<endl;
		cout<<"\t\t ";system("pause");
		return false;
	}
	if (option == 1)
	{
		//Kiểm tra năm học có tồn và tạo ra thư mục con của Semester chứa năm học đó
		if(String_InFile("Years.csv",year_name)) 
		{
			string dir = ".\\Semesters\\" + year_name + "\\";
			Directory_Create(dir);
		}
		Semester_Create(year_name,dmy);
		system("cls");
		return true;
	}
	else if (option == 2)
	{
		bool run = true;
		while(run){
		
			run  = Semester_Delete(year_name);
		}
		system("cls");
		return true;
	}
	else
	{
		system("cls");
		return false;
	}
}
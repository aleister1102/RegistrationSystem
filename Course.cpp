#include "Header\Course.h"
#include "Header\Class.h"
#include "Header\Year.h"
#include "Header\Menu.h"
#include "Header\File.h"
#include "Header\Semester.h"
#include "Header\Convert.h"
#include "Header\Node Process.h"
#include "Header\Vector.h"
#include "Header\Student.h"

//*Kiểm tra tính hợp lệ của môn học nhập vàp
//@param c Kiểu dữ liệu môn học
//@return True - nếu môn học hợp lệ
bool Valid_Course(Course c)
{
	if (c.cre < 0 || c.capacity < 0 )
	{
			return false;
	}
	return true;
}
//*Phân loại ngày của môn học
//@param day Ngày của môn học dạng số
//@return Chuỗi ngày sau khi phân loại
string Course_Day_Classify(int day)
{
	switch (day)
	{
	case 1: return "Monday";
	case 2: return "Tuesday";
	case 3: return "Wednesday";
	case 4: return "Thursday";
	case 5: return "Friday";
	default:
		return "Saturday";
	}
}
//*Phân loại tiết học của môn học
//@param session Tiết học dạng số
//@return Chuỗi tiết học sau khi phân loại
string Course_Session_Classify(int session)
{
	switch (session)
	{
	case 1: return "S1";
	case 2: return "S2";
	case 3: return "S3";
	default:
		return "S4";
	}
}
//*Nhập tên môn học và kiểm tra
//@return Kiểu dữ liệu môn học
Course Course_Input(){
	Course new_course;
	do {
		cout << "\t\t ID: "; getline(cin, new_course.id);
		cout << "\t\t Course Name: "; getline(cin, new_course.name); 
		cout << "\t\t Teacher Name: "; getline(cin, new_course.teacher);
		cout << "\t\t Number of credits: "; cin >> new_course.cre;
		cout << "\t\t Maximum students: "; cin >> new_course.capacity;
		new_course.day=Course_Day_Classify(Course_Day());
		new_course.session=Course_Session_Classify(Course_Session());
	} while (Valid_Course(new_course) == false);
	return new_course;
}
//*Tạo môn học mới
//@param semester_path Đường dẫn đến học kỳ
//@param faculty Tên của khoa 
void Course_Create(string semester_path,string faculty)
{
	//Nhập môn học bằng tay
	string new_course = Course_ToString(Course_Input());
	//Tạo file cho môn học
	string course_path = Get_Course_Path(new_course, faculty);
	//Loại đi trường hợp course đã tạo
	if(File_Exist(course_path)) return;
	File_Create(course_path);
	//Cho môn học vào file lưu giữ của khoa
	new_course +="," + faculty;
	File_Append(semester_path, new_course);
}
//*Hiển thị các môn học
//@param semester_path Đường dẫn tới học kỳ
//@param faculty Khoa hiện hành
//@return Số môn học đếm được
int Courses_Display(string semester_path,string faculty)
{
	system("cls");
	//Mở file semester lên và đọc chuỗi
	ifstream f(semester_path);
	int count=1;
	if(f.is_open())
	{
		string reader;
		//Bỏ qua thông tin về thời gian
		for(int i=0;i<4;i++)
		{
		getline(f,reader);
		cout<<"\t\t -----------------------"<<endl;
		cout<<"\t\t -----------------------"<<endl;
		cout<<"\t\t LIST OF CREATED COURSES"<<endl;
		{
			getline(f,reader,'\n');
			if(reader=="") break;
			//Thay dấu để xuất ra trông đẹp hơn
			String_Replace(reader,",","  -  ");
			cout<<"\t\t "<<count<<". "<<reader<<endl;
			count+=1;
		}	
	}
	f.close();
	//Nếu không có môn học nào thì xuất thông báo
	if(count<2) {
		cout<<"\t\t -----------------------------------------"<<endl;
		cout<<"\t\t Wrong Faculty or this Faculty does not have any courses !!!!!!!"<<endl;
		cout<<"\t\t ";system("pause");
	}
	return count-1;
}
//*Chọn lựa môn học
//@param semester_path Đường dẫn tới học kỳ
//@return Sự lựa chọn môn học (Bằng 0 nếu không có môn nào)
int Course_Select(string faculty)
{
	string courses= ".\\Courses\\" + faculty + "\\Courses.csv";
	//Xuất danh sách các môn học
	int limited_course = Courses_Display(courses, faculty);
	if(limited_course<1) return 0;
	cout<<"\t\t Choose course for modify: ";
	//Chọn môn học cần chỉnh sửa
	return Valid_Data(limited_course);
}
//*Lấy đường dẫn môn học đã Chọn
//@param course_string Thông tin môn học //@param faculty Khoa hiện hành
//@return Đường dẫn môn học
string Get_Course_Path(string course_string, string faculty)
{
	string course_folder = ".\\Courses\\" + faculty + "\\";
	Course info = String_ToCourse(course_string);
	string course_name = info.name + "_" + info.teacher;
	return Make_Path(course_folder, course_name);
}
string Get_Course_Faculty(string course)
{
	int pos = course.find_last_of(",", course.length());
	return course.substr(pos + 1, course.length() - pos - 1);
}
//*Khởi tạo cho các tính năng của môn học
//@param &semester_path Đường dẫn đến học kỳ
//@param dmy Ngày tháng hiện tại
bool Course_Init(string &semester_path,date dmy)
{
	//Cho năm học cần tạo môn học là năm nay
	string year_name = to_string(dmy.year)+"-"+to_string(dmy.year+1);
	//Tạo đường dẫn cho năm và kiểm tra xem nó có tồn tại hay không 
	string year_path = Make_Path(".\\Years\\",year_name);
	if (File_Exist(year_path)==false) 
	{
		cout<<"\t\t This year was not created !"<<endl;
		cout<<"\t\t ";system("pause");
		return false;
	}
	//Nếu năm tồn tại thì cho chọn học kỳ của năm đó
	int limited_semester = Semester_Display(year_name);
	semester_path = Semester_Select(year_name);
	if(semester_path=="OUT")
		return false;
	return true;
}

bool Course_Proc(int option,string semester_path)
{
	if (option == 1)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(),1);
		if(faculty=="OUT") return false;
		//Tạo môn học
		Course_Create(semester_path,faculty);
		system("cls");
		return true;
	}	
	else if(option ==2)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(),1);
		if(faculty=="OUT") return false;
		//Xóa môn học
		bool run = true;
		while(run){
			// run  = Course_Delete(faculty);
		}
		system("cls");
		return true;
	}
	else if(option ==3)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(),1);
		if(faculty=="OUT") return false;
		//Cập nhật môn học
		// Course_Update(semester_path,faculty);
		system("cls");
		return true;
	}
	else if(option ==4)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(),1);
		if(faculty=="OUT") return false;
			
		Courses_Display(semester_path,faculty);
		cout<<"\t\t ";system("pause");
		system("cls");
		return true;
	}
	else
	{
		system("cls");
		return false;
	}
}

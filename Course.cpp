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
	Course new_course = Course_Input();
	//Tạo file cho môn học
	string faculty_folder = ".\\Courses\\" + faculty + "\\";
	string course_name = new_course.name + "_" + new_course.teacher;
	string course_path = Make_Path(faculty_folder+"List of courses\\",course_name);
	cout<<"Course path "<<course_path<<endl;
	system("pause");
	//Loại đi trường hợp course đã tạo
	if(File_Exist(course_path)) return;
	File_Create(course_path);
	//Cho môn học vào semester của năm học
	string course_string = Course_ToString(new_course);
	File_Append(semester_path,course_string);
}
//*Hiển thị các môn học
//@param semester_path Đường dẫn tới học kỳ
//@return Số môn học đếm được
int Courses_Display(string semester_path)
{
	//Mở file semester lên và đọc chuỗi
	ifstream f (semester_path);
	int count=1;
	if(f.is_open())
	{
		//Đọc thời gian của học kỳ
		string reader; 
		getline(f,reader,'\n');
		View_Semester_Time(reader);
		//Đọc thời gian đăng ký học phần
		getline(f,reader,'\n');
		View_Registration_Time(reader);
		//Đọc các môn học hiện có
		cout<<"\t\t -----------------------"<<endl;
		cout<<"\t\t -----------------------"<<endl;
		cout<<"\t\t LIST OF CREATED COURSES"<<endl;
		while(!f.eof())
		{
			getline(f,reader,'\n');
			if(reader=="") break;
			String_Replace(reader,",","  -  ");
			cout<<"\t\t "<<count<<". "<<reader<<endl;
			count+=1;
		}	
	}
	f.close();
	return count-1;
}
//*Chọn lựa môn học
//@param semester_path Đường dẫn tới học kỳ 
int Course_Select(string semester_path)
{
	//Xuất danh sách các môn học
	int limited_course = Courses_Display(semester_path);
	if(limited_course<1) return false;
	cout<<"\t\t "<<limited_course+1<<". Exit"<<endl;
	cout<<"\t\t Choose course for modify: ";
	//Chọn môn học cần chỉnh sửa
	return Valid_Data(limited_course+1);
}
//*Xóa môn học
//@param semester_path Đường dẫn tới học kỳ
//@para faculty Tên khoa
//@return True nếu cần utilize
bool Course_Delete(string semester_path,string faculty)
{
	int choice = Course_Select(semester_path);
	if(choice ==0) return false ;
	//Vừa xóa môn học trong file semester vừa lấy ra được môn học dạng string
	string course_folder = ".\\Courses\\" + faculty + "\\";
	string course_string = File_Line_Delete(semester_path,2,choice);
	//Tạo đường dẫn cho việc xóa file
	string arr[7];
	Course info = String_ToCourse(course_string,arr);
	string course_name  = info.name + "_" + info.teacher;
	course_folder+="List of courses\\";
	string course_path = Make_Path(course_folder,course_name);
	remove(course_path.c_str());
	return true;
}

//TODO Hoàn thiện hàm cập nhật course
//*Kiểm tra tên môn học trong chuỗi môn học
//@param course Chuỗi môn học @param course_name Tên môn học
//@return True nếu tồn tại tên môn học trong chuỗi lớn
bool Course_Detect(string course_string,string course_name)
{
	//Todo Xóa ba dòng tiếp theo nếu code đã chạy ổn
	int pos =course_string.find_first_of("_",0);
	cout<<"Check "<<course_name<<" in "<<course_string<<endl;
	system("pause");

	if(course_string.find(course_name,0)!=string::npos)
		return true;
	return false;
}
//*Tìm môn học có trong file sinh viên
//@param student_path File sinh viên
//@param course_name Tên môn học
//@return Số thứ tự dòng tìm thấy môn học (0 nếu không tìm được)
int Course_Find_in_Student(string student_path,string course_name)
{
	cout<<"Check "<<course_name<<" in "<<student_path<<endl;
	system("pause");
	fstream f(student_path,ios::in);
	int count=1;
	if(f.is_open())
	{
		while(!f.eof()){
			string course_string;
			getline(f,course_string);
			if(CourseString_To_CourseName(course_string) == course_name)
			{
				cout<<"Find course at line: "<<count<<endl;
				return count;
			}
			count+=1;
		}
		return 0;
	}
}
//*Cập nhật môn học
//@param semester_path Đường dẫn học kỳ
//@param faculty Tên khoa
void Course_Update(string semester_path,string faculty)
{
	//Cho người dùng chọn lựa các field cần cập nhật
	int choice = Course_Select(semester_path);
	vector<int> choices;
	int choice_number = Course_Update_Menu(choices);
	if(choice_number==0) return; 
	//Xóa dòng đó trong file học kỳ và lấy ra để cập nhật
	string course_string = File_Line_Delete(semester_path,2,choice);
	string course_info[7];
	Course c = String_ToCourse(course_string,course_info);

	//Thực thi việc cập nhật
	for(int i=0;i<choice_number;i++)
	{
		cout<<"Current option: "<<choices[i]<<endl;
		switch (choices[i])
		{
		case 1: {
			cout<<"\t\t Type new ID: "<<endl;
			cout<<"\t\t ";getline(cin,c.id);
			break;
		}
		case 2:{
			cout<<"\t\t Type new Course's Teacher: "<<endl;
			cout<<"\t\t ";getline(cin,c.teacher);
			
			break;
		}
		case 3:{
			cout<<"\t\t Type new Course's Credits: "<<endl;
			cout<<"\t\t ";cin>>c.cre;
			cin.ignore();
			break;
		}
		case 4:{
			cout<<"\t\t Type new Maximum Students: "<<endl;
			cout<<"\t\t ";cin>>c.capacity;
			cin.ignore();
			break;
		}
		case 5:{
			cout<<"\t\t Type new Course's Day: "<<endl;
			cout<<"\t\t ";getline(cin,c.day);
			break;
		}
		case 6:{
			cout<<"\t\t Type new Course's Session: "<<endl;
			cout<<"\t\t ";getline(cin,c.session);
			break;
		}
		default:
			break;
		}
	}
	//Chuyển kiểu dữ liệu môn học đã thay đổi lại thành chuỗi
	course_string = Course_ToString(c);
	//Cập nhật trong file học kỳ
	File_Line_Update(semester_path,2,choice,course_string);
	//Thực hiện đổi tên file môn học trong thư mục gốc với teacher mới
	string course_folder = ".\\Courses\\" + faculty + "\\List of courses\\";
	string course_name = c.name + "_" + c.teacher;
	string course_path =  Make_Path(course_folder,course_name);
	string new_course_path = Make_Path(course_folder,c.name+"_"+c.teacher);
	rename(course_path.c_str(),new_course_path.c_str());
	cout<<"New path of course: "<<new_course_path<<endl;
	//Đổi tên giáo viên trong file đăng ký của Hs
	Student_Update(new_course_path,c.teacher);
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
	semester_path = Semester_Selection(year_name);
	if(semester_path=="OUT")
		return false;
	return true;
}
//*Xử lý các tính năng của môn học
//@param option Sự lựa chọn tính năng
//@param dmy Ngày tháng hiện tại
//@return True nếu cần recycle
bool Course_Proc(int option,date dmy)
{
	string semester_path;
	//Chọn năm học và học kỳ
	int run = Course_Init(semester_path,dmy);
	if(run == false) {
		return false;
	}
	string faculty = Faculty_Name(Department_Menu_Disp(),1);
	if (option == 1)
	{
		//Tạo môn học
		Course_Create(semester_path,faculty);
		system("cls");
		return true;
	}
	else if(option ==3)
	{
		//Xóa môn học
		//!Chưa xóa ở file sinh viên
		bool run = true;
		while(run){
			run  = Course_Delete(semester_path,faculty);
		}
		system("cls");
		return true;
	}
	else if(option ==2)
	{
		//Cập nhật môn học
		Course_Update(semester_path,faculty);
		cout<<"\t\t ";system("pause");
		system("cls");
		return true;
	}
	else if(option ==4)
	{
		Courses_Display(semester_path);
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

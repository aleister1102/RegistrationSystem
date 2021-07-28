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
	string course_path = Make_Path(faculty_folder,course_name);
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
int Courses_Display(string semester_path,string faculty)
{
	system("cls");
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
		cout<<"\t\t 0. Back"<<endl;
		while(!f.eof())
		{
			getline(f,reader,'\n');
			if(reader=="") break;
			//Kiểm tra môn học đó có tòn tại trong khoa
			string course_folder = ".\\Courses\\" + faculty + "\\";
			string course_name = CourseString_To_CourseName(reader);
			string course_path = Make_Path(course_folder,course_name);
			if(File_Exist(course_path)==false) continue;
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
	}
	return count-1;
}
//*Chọn lựa môn học
//@param semester_path Đường dẫn tới học kỳ
//@return Sự lựa chọn môn học (Bằng 0 nếu không có môn nào)
int Course_Select(string semester_path,string faculty)
{
	//Xuất danh sách các môn học
	int limited_course = Courses_Display(semester_path,faculty);
	if(limited_course<1) return 0;
	cout<<"\t\t Choose course for modify: ";
	//Chọn môn học cần chỉnh sửa
	return Valid_Data(limited_course);
}
//*Xóa môn học
//@param semester_path Đường dẫn tới học kỳ
//@para faculty Tên khoa
//@return True nếu cần utilize
bool Course_Delete(string semester_path,string faculty)
{
	int choice = Course_Select(semester_path,faculty);
	if(choice == 0) return false ;
	//Vừa xóa môn học trong file semester vừa lấy ra được môn học dạng string
	string course_folder = ".\\Courses\\" + faculty + "\\";
	string course_string = File_Line_Delete(semester_path,2,choice);
	//Tạo đường dẫn cho việc xóa môn học trong file sinh viên và xóa file 
	string arr[7];
	Course info = String_ToCourse(course_string,arr);
	string course_name  = info.name + "_" + info.teacher;
	string course_path = Make_Path(course_folder,course_name);
	//Xóa môn học trong file sinh viên
	ifstream f(course_path);
	while(!f.eof()){
		string reader;
		getline(f,reader);
		if(reader=="") continue;//Chuỗi rỗng thì bỏ qua
		string student_folder = ".\\Students\\Students for Enrollment\\";
		string student_path = Make_Path(student_folder,reader);
		//Tìm môn học trong file sinh viên
		int line = Course_Find_in_Student(student_path,course_name);
		//Và xóa môn học đó
		File_Line_Delete(student_path,0,line);
	}
	f.close();
	//Xóa file môn học
	remove(course_path.c_str());
	return true;
}

//*Tìm môn học có trong file sinh viên
//@param student_path File sinh viên
//@param course_name Tên môn học
//@return Số thứ tự dòng tìm thấy môn học (0 nếu không tìm được)
int Course_Find_in_Student(string student_path,string course_name)
{
	ifstream f(student_path);
	int count=1;
	if(f.is_open())
	{
		while(!f.eof()){
			string course_string;
			getline(f,course_string);
			//Đọc tên môn học và so sánh với môn học cần thay đổi
			if(course_string == course_name)
			{
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
	//Cho người dùng chọn môn học cần cập nhật
	int choice = Course_Select(semester_path,faculty);
	if(choice==0) return;
	vector <string> choices;
	//Cho người dùng chọn lựa các field cần cập nhật
	int choice_number = Course_Update_Menu(choices);
	if(choice_number==0) return; 
	//Xóa dòng đó trong file học kỳ và lấy ra để cập nhật
	string course_string = File_Line_Delete(semester_path,2,choice);
	cout<<"\t\t ---------------------------------"<<endl;
	cout<<"\t\t Old Course Name:  "<<course_string<<endl;
	string course_info[7];
	Course c = String_ToCourse(course_string,course_info);
	string teacher_temp = course_info[2];//Lưu tên giáo viên cũ
	
	//Thực thi việc cập nhật
	
	for(int i=0;i<choices.size();i++)
	{
		cout<<"Current option: "<<choices[i]<<endl;
		switch (stoi(choices[i]))
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
	string course_folder = ".\\Courses\\" + faculty + "\\";
	string course_name = c.name + "_" + teacher_temp;
	string course_path =  Make_Path(course_folder,course_name);
	string new_course_path = Make_Path(course_folder,c.name+"_"+c.teacher);
	int check = rename(course_path.c_str(),new_course_path.c_str());
	if (check == 1) cout << "Error to rename!";
	//Đổi tên giáo viên trong file đăng ký của Sinh viên
	if(teacher_temp==c.teacher) return; //Tên giáo viên không đổi thì out
	Student_Course_Update(new_course_path,c.teacher);
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
			run  = Course_Delete(semester_path,faculty);
		}
		system("cls");
		return true;
	}
	else if(option ==3)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(),1);
		if(faculty=="OUT") return false;
		//Cập nhật môn học
		Course_Update(semester_path,faculty);
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

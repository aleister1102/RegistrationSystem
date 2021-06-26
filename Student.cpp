#include "Header\Year.h"
#include "Header\Class.h"
#include "Header\Node Process.h"
#include "Header\Login.h"
#include "Header\File.h"
#include "Header\Convert.h"
#include "Header\Student.h"
#include "Header\Menu.h"
#include "Header\Vector.h"
#include "Header\Course.h"

//*Dùng đường dẫn đến file lớp để tìm thông tin học sinh (dùng cho việc đăng nhập)
//@param class_path Đường dẫn đến lớp học
//@param user Thông tin tài khoản và mật khẩu
//@return Kiểu dữ liệu thông tin sinh viên
Student Find_Student_Info(string class_path, Account user)
{
	Student s;
	string arr[8];
	fstream f(class_path, ios::in);
	if(File_Exist(class_path))
	{
		while(!f.eof())
		{
			string reader;
			getline(f,reader);
			string id = reader.substr(2,8);
			if(id == user.username)
			{
                s = String_ToStudent(reader,arr);
                break;
			}
		}
	}
	f.close();
	return s;
}
//*Nhập học sinh vào danh sách lớp và các thư mục cần thiết
//@param class_path Đường dẫn đến file lớp học
void Student_Import(string class_path)
{
    if(class_path=="OUT") return;
    //Nhập file cần import học sinh
    string folder = ".\\Students\\Students' Info\\";
    string import = File_Import(folder);
    if(import=="OUT") return;
    
    ifstream read(import);
    while(!read.eof())
    {
        //Đọc file import
        string student;
        getline(read,student);
        if(student=="") continue;
        //Tạo file học sinh
        string arr[8];
        Student s = String_ToStudent(student,arr);
        string student_folder = ".\\Students\\Students for Enrollment\\";
        string student_file_name = arr[1]+"_"+arr[2];
        string student_file_path = Make_Path(student_folder,student_file_name);
        if(File_Exist(student_file_path)) continue;
        File_Create(student_file_path);
        //Ghi học sinh vào file lớp
        File_Append(class_path,student);
        //Ghi tài khoản mật khẩu vào file Account
        string account=".\\Accounts\\acc_sv.csv";
        string user_pass_path = arr[1] +","+ arr[7] + ","+class_path;
        File_Append(account,user_pass_path);
    }
    read.close();
}
//*Xóa một học sinh đơn lẻ có trong lớp
//@param class_path Đường dẫn tới lớp
//@return True nếu cần recycle
bool Student_Delete(string class_path){
    
    //Xuất danh sách học sinh
    int limited_student = Student_Display(class_path);
    if(limited_student<1) return false;
    //Chọn học sinh để xóa
    cout<<"\t\t Press '-1' if you want to exit!"<<endl;
    cout<<"\t\t Choose student to modify: ";
    int choice = Valid_Data(limited_student);
    if(choice<1) return false;
    //Xóa học sinh trong file lớp
    string student_string = File_Line_Delete(class_path,0,choice);
    //Xóa học sinh trong file account
    string account = ".\\Accounts\\acc_sv.csv";
    ifstream f (account,ios::in);
    int count = 1;
    int line = -1;
    while(!f.eof())
    {
        string reader;
        getline(f,reader);
        if(reader.substr(0,8)==student_string.substr(2,8))
            {
                line = count;
                break;
            }
        count+=1;
    }
    f.close();
    File_Line_Delete(account,0,line);
    //Xóa file học sinh
    string arr[8];
    Student s = String_ToStudent(student_string,arr);
    string student_folder = ".\\Students\\Students for Enrollment\\";
    string student_file_path = Make_Path(student_folder,arr[1]+"_"+arr[2]);
    remove(student_file_path.c_str());

    return true;
}
//*Hiển thị học sinh có trong lớp
//@param class_path Đường dẫn của lớp cần truy cập
//@return Số lượng học sinh đếm được
int Student_Display(string class_path)
{
    system("cls");
    cout<<"\t\t Current Students in class: "<<endl;
    cout<<"\t\t (No-ID-Name-Gender-Faculty-Birthdate-Social ID)"<<endl;
    cout<<"\t\t -----------------------------------------------"<<endl;
    
    int count=0; 
    fstream f(class_path,ios::in);
    while(!f.eof())
    {
        string reader;
        getline(f,reader);
        if(reader!=""){
            count+=1;
        }
        else{
            continue;
        }
        string arr[8];
        String_ToStudent(reader,arr);
        cout<<count<<". ";
        for(int i=0;i<8;i++)
        {
            cout<<arr[i]<<" \t ";
            if(i==7) cout<<endl;
        }
    }
    f.close();
    if(count<1)
    {
        cout<<"\t\t This class does not have any students"<<endl;
    }
    cout<<"\t\t ";system("pause");
    return count;
}
//*Cập nhật môn học có trong file sinh viên (lấy DS SV từ file môn học). 
//!Hàm này giữ cho thứ tự môn học không đổi
//@param course_path Đường dẫn đến học kỳ.
//@param new_course_teacher Giáo viên mới của môn học.
void Student_Update(string course_path,string new_course_teacher)
{
	//Lấy ra tên môn học
	string student_folder = ".\\Students\\Students for Enrollment\\";
	string course_string=Path_ToName(course_path);
	string course_name = CourseString_To_CourseName(course_string);
	//
	ifstream f(course_path);
	if(f.is_open()){
		while(!f.eof())
		{
			//Đọc sinh viên từ file môn học
			string student;
			getline(f,student);
			string student_path = Make_Path(student_folder,student);
			//Nếu như chuỗi rỗng thì out vòng lặp
			if(Path_ToName(student_path)=="") continue;
			cout<<"Student path: "<<student_path<<endl;
			system("pause");
			//Tìm môn học trong file student
			int line = Course_Find_in_Student(student_path,course_name);
			if(line!=0)
			{
				//Xóa dòng môn học cũ trong file student
				string course_string = File_Line_Delete(student_path,0,line);
				cout<<"Course in student file: "<<course_string<<endl;
				system("pause");
				//Thay giáo viên mới
				int size = course_string.size();
				int pos = course_string.find_last_of("_",size);
				course_string.replace(pos+1,size-pos,new_course_teacher);
				cout<<"New course string: "<<course_string<<endl;
				system("pause");
				//Cập nhật (nói khác đi là chèn) vào tên môn học cũ
				File_Line_Update(student_path,0,line,course_string);
			}
		}
	}
	f.close();
}
//*Khởi tạo đường dẫn cần thiết cho các tính năng của students
//@return Đường dẫn của lớp học
string Student_Init()
{
    //Chọn năm
    string year_name=Year_Select();
    if(year_name=="OUT") return "OUT";
    //Chọn lớp 
    int line_number ;
    string class_path=Class_Select(year_name,line_number);
    if(class_path=="OUT") return "OUT"; 
    return class_path;
}
//*Xử lý các tính năng của Student
//Sự lựa chọn tính năng
//True nếu hàm cần dùng lại, false nếu không
bool Student_Proc_Active(int option,string class_path)
{
    if(option==1)
    {
        Student_Import(class_path);
        system("cls");
        return true;
    }
    else if(option==2)
    {
        bool run =true;
        while(run)
        {
            run = Student_Delete(class_path);
        }
        system("cls");
        return true;
    }
    else if(option ==3)
    {
        Student_Display(class_path);
        system("cls");
        return true;
    }
    else{
        return false;
    }
}

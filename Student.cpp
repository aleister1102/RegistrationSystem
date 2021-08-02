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
Student Get_Student_Info(string class_path, Account user)
{
    Student s;
	fstream f(class_path, ios::in);
	if(File_Exist(class_path))
	{
		while(!f.eof())
		{
			string reader;
			getline(f,reader);
            if(reader=="") continue;
			string id = reader.substr(2,8);
			if(id == user.username)
			{
                s = String_ToStudent(reader);
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
        cout<<student<<endl;
        system("pause");
        if(student=="") continue;
        //Tạo file học sinh
        Student s = String_ToStudent(student);
        string student_folder = ".\\Students\\Students for Enrollment\\";
        string student_file_name = to_string(s.id)+"_"+s.name;
        string student_file_path = Make_Path(student_folder,student_file_name);
        cout<<student_file_path<<endl;
        system("pause");
        if(File_Exist(student_file_path)) continue;
        File_Create(student_file_path);
        //Ghi học sinh vào file lớp
        File_Append(class_path,student);
        //Sắp xếp lại số thứ tự học sinh
        Student_Arrange(class_path);
        //Ghi tài khoản mật khẩu vào file Account
        string account=".\\Accounts\\acc_sv.csv";
        string user_pass_path = to_string(s.id) +","+ s.user.password + ","+class_path;
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
    Student s = String_ToStudent(student_string);
    string student_folder = ".\\Students\\Students for Enrollment\\";
    string student_file_path = Make_Path(student_folder,s.id+"_"+s.name);
    remove(student_file_path.c_str());

    return true;
}
//*Sắp xếp lại số thứ tự trong file học 
//@param class_path Đường dẫn tới lớp
void Student_Arrange(string class_path)
{
	//Cho học sinh vào vector
    vector<string> students = File_ToVector(class_path);
    //Thay số thứ tự
	for(int i=0;i<students.size();i++)
	{
		students[i].replace(0,1,to_string(i+1));
	}
    //Clear file cũ
    File_Clear(class_path);
    //Cho danh sách học sinh mới vào
	Vector_ToFile(class_path,students);
}
//*Hiển thị học sinh có trong lớp
//@param class_path Đường dẫn của lớp cần truy cập
//@return Số lượng học sinh đếm được
int Student_Display(string class_path)
{
    system("cls");
    //Sắp xếp lại số thứ tự học sinh
    Student_Arrange(class_path);
    cout<<"\t\t Current Students in class: "<<endl;
    cout<<"\t\t (No-ID-Name-Gender-Faculty-Birthdate-Social ID)"<<endl;
    cout<<"\t\t -----------------------------------------------"<<endl;
    
    cout << "\t\t 0. Back" << endl;
    int count=0; 
    fstream f(class_path,ios::in);
    while(!f.eof())
    {
        string reader;
        getline(f,reader);
        if(reader=="") continue;
        count+=1;
        //Thay dấu phẩy thành dấu gạch ngang
        String_Replace(reader,",","  -  ");
        cout<<reader<<endl;
    }
    f.close();
    if(count<1)
    {
        cout<<"\t\t This class does not have any students"<<endl;
    }
    cout<<"\t\t ";system("pause");
    return count;
}
//*Khởi tạo đường dẫn cần thiết cho các tính năng của students
//@return Đường dẫn của lớp học
string Student_Init(string year_name)
{
    //Kiểm tra sự tồn tại của lớp
    string year_path = Make_Path(".\\Years\\",year_name);
	if(File_Exist(year_path)==false) 
	{
		cout<<"\t\t This year was not created"<<endl;
		cout<<"\t\t ";system("pause");
		return "OUT";
	}
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

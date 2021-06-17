#include "Header/Year.h"
#include "Header/Class.h"
#include "Header/Node Process.h"
#include "Header/Login.h"
#include "Header/File.h"
#include "Header/Convert.h"
#include "Header/Student.h"

//Xóa một học sinh đơn lẻ có trong lớp
bool Student_Delete(string class_path){
    
    int limited_student = Student_Display(class_path);
    if(limited_student<1) return false;
    cout<<"\t\t Choose student to modify: ";
    int option = Valid_Data(limited_student);
    int count =1;
    names list = Init_List();
    fstream f(class_path,ios::in|ios::out);

    while(!f.eof())
    {
        string reader;
        getline(f,reader);
        if(count!=option)
        {
            //Cho học sinh không bị xóa vào DSLK
            name * node = Create_Node(reader);
            Add_Last(list,node);
        }
        else{
            //Tức là đã có học sinh bị loại khỏi danh sách
            limited_student-=1;
        }
        count+=1;
    }
    f.close();
    //Xóa cả file
    File_Clear(class_path);
    //Truyền dữ liệu lại từ list vào file
    ReInput_fromList(class_path,list);

    //Nếu học sinh không còn thì thoát khỏi hàm delete (không dùng lại nữa)
    if(limited_student<1)
    {
        return false;
    }
    return true;
}
//Nhập học sinh vào danh sách
//Tên của năm cần truy cập, đường dẫn tới lớp cần truy cập
void Student_Import(string class_path)
{
    if(class_path=="!") return;
    string folder = ".\\Students\\Students' Info\\";
    string path = File_Import(folder);
    if(path=="!") return;

    
    fstream f(path,ios::in);
    names list = Init_List();
    while(!f.eof())
    {
        string reader;
        getline(f,reader);
        name* node = Create_Node(reader);
        Add_Last(list,node);
    }
    f.close();
    Output_List(list);
    ReInput_fromList(class_path,list);
}
//Hiển thị học sinh có trong lớp
//Đường dẫn của lớp cần truy cập
int Student_Display(string class_path)
{
    system("cls");
    int count=0;
    fstream f(class_path,ios::in);
    cout<<"\t\t Current Students in class: "<<endl;
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
        cout<<"\t\t "<<count<<".  "<<reader<<endl;
    }
    f.close();

    if(count<1)
    {
        cout<<"\t\t This class does not have any students"<<endl;
        cout<<"\t\t ";system("pause");
    }
    return count;
}

//Xử lý các tính năng của menu student
//Sự lựa chọn tính năng
//True nếu hàm cần dùng lại, false nếu không
bool Student_Menu_Proc(int option)
{
    if(option==1)
    {
        string year_name = Year_Selection();
        if(year_name=="!") return true;
        Student_Import(Class_Selection(year_name));
        system("cls");
        return true;
    }
    else if(option==2)
    {
        string year_name=Year_Selection();
        if(year_name=="!") return true;
        string class_path=Class_Selection(year_name);
        if(class_path=="!") return true;
        bool run =true;
        while(run)
        {
            run = Student_Delete(class_path);
        }
        system("cls");
        return true;
    }
    else if(option==3)
    {
        string year_name=Year_Selection();
        if(year_name=="!") return true;
        string class_path=Class_Selection(year_name);
        if(class_path=="!") return true;
        File_Clear(class_path);
        return true;
    }
    else if(option ==4)
    {
        string year_name = Year_Selection();
        string class_path = Class_Selection(year_name);
        Student_Display(class_path);
        system("cls");
        return true;
    }
    else{
        return false;
    }
}

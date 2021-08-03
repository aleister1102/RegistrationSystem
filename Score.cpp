#include "Header/Menu.h"
#include "Header/Class.h"
#include "Header/File.h"
#include "Header/Student.h"
#include "Header/Vector.h"
#include "Header/Convert.h"
#include "Header/Score.h"
//*Nhập tên môn học có bảng điểm vào hệ thống

void Score_Import()
{
    string folder = ".\\Students\\Students' ScoreBoard\\Import\\";
    string import = File_Import(folder);
    vector<string> list = File_ToVector(import);
    string course_name = Path_ToName(import);
    File_Append(Make_Path(folder, "Import ScoreBoard"),course_name);
}
//*Xử lý và điều hướng các hàm tính năng của năm
//@param option Lựa chọn tính năng @param semester_path đường dẫn tới học kỳ
//@return True nếu cần dùng tiếp, false nếu muốn thoát ra hẳn
bool Score_Proc(int option, string semester_path)
{
    if (option == 1)
    {
        string faculty = Faculty_Name(Department_Menu_Disp(), 1);
        if (faculty == "OUT")
            return false;
        //Student_Export(semester_path,faculty);
        cout<<"\t\t ";system("pause");
        return true;
    }
    if (option == 2)
    {
        Score_Import();
        cout<<"\t\t ";system("pause");
        return true;
    }
    else
    {
        system("cls");
        return false;
    }
}

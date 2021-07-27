#include "Header/Menu.h"
#include "Header/Class.h"
#include "Header/Student.h"
#include "Header/Score.h"
//*Xử lý và điều hướng các hàm tính năng của năm
//@param option Lựa chọn tính năng @param semester_path đường dẫn tới học kỳ
//@return True nếu cần dùng tiếp, false nếu muốn thoát ra hẳn
bool Score_Proc(int option,string semester_path)
{
    if (option == 1)
    {
        string faculty = Faculty_Name(Department_Menu_Disp(), 1);
        if (faculty == "OUT")
            return false;
        Student_Export(semester_path,faculty);
        cout<<"\t\t ";system("pause");
        return true;
    }
    else
    {
        system("cls");
        return false;
    }
}
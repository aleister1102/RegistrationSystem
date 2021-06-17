#include "Header/MainSource.h"

//Main menu
int Main_Menu_Disp();
bool Main_Menu_Proc(int option);
//Sub menu
bool Login_Proc(int option);
int Login_Disp();
void AboutUs();

//Admin
bool Display_Mode_Admin(Account info, date dmy);
int Admin_Disp_Begin();
bool Admin_Proc_Begin(int option, Account info, date dmy);
////Student//
bool Display_Mode_Student(Student info, date dmy);
int Student_Menu_forStudent();
bool Student_Proc_forStudent(int option,Student info,date dmy);
////Year menu//
int Year_Menu_Disp();
////Class menu//
int Class_Menu_Disp();
int Class_Create_Mod_Menu();
////Semester menu//
int Semester_Menu_Disp();
////Course Menu//
int Course_Menu_Disp();
////Student Menu//
int Student_Menu_Disp();
////Department menu//
int Department_Menu_Disp();
////System menu//
int Training_System_Menu_Disp();

int Valid_Data(int limit);

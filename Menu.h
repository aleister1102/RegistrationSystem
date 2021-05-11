#include "MainSource.h"
#include"LOGIN.h"

//Main menu
int Main_Menu_Disp();
bool Main_Menu_Proc(int option);
//Sub menu
bool Login_Proc(int option);
int Login_Disp();
void AboutUs();

//Admin
int Admin_Disp();
bool Admin_Proc(int option, user info, date dmy);
//Student
int Student_Disp();
bool Student_Proc(int option, user info, date dmy);

//Year menu
int Year_Menu_Disp();
bool Year_Proc_Active(int option,int time);
int Years_Display();

//Class menu
int Class_Menu_Disp();
bool Class_Proc_Active(string year_name, int option, int time);
int Classes_Display(string year);

//Semester menu
int Semester_Menu_Disp();
//Department menu
int Department_Menu_Disp();
//System menu
int Training_System_Menu_Disp();


int Valid_Data(int limit);

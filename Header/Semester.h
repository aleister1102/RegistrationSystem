#include "MainSource.h"
void View_Semester_Time(string time);
void View_Registration_Time(string time);

void Semester_Time_Create(string year_name,string semester_suffix,string semester_path);
void Semester_Create(string year_name,date dmy);

int Semester_Display(string year_name);

string Semester_Select(string year_name);

bool Semester_Proc(string year_name,date dmy,int option);

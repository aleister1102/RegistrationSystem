#include "MainSource.h"
string Extension(string name, int option);
string Make_Path(string pre_folder, string file_name);
string Path_ToName(string s);
int String_ToInt(string s);
int Year_ToInt(string year_name);
string Date_toString(date dmy);
date String_ToDate(string dmy);
Student String_ToStudent(string info,string arr[8]);
Course String_ToCourse(string info,string arr[7]);
string Course_ToString(Course c);
string CourseString_To_CourseName(string course_string);
void String_Replace(string &s,string target,string change);
string* File_toStringArray(string path);
names File_to_LinkList(string path);


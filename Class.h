#include "MainSource.h"


int Create_Type();
void Input_Class(string year_name, string class_name);

////Create Class option 1//
string Year_Selection();
string Create_Directory(string year_name);
string File_Import();

////Create Class option 2//
bool Duplicated_Class(string year_name, string check);
string Department_Name(int depart,int system); 
string Create_Class_Single(string year_name, int time);

////Delete Class(es)//
void Class_Delete(string year_path, int quanti);
void Class_Clear(string year_path);
//Delete directory
void Delete_Directory(string dir);

////Classes displaying//
int Classes_Display(string year_path);



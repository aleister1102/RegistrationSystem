#include "MainSource.h"

//Converting function
string Int_ToString(int n);
string CSV_ToName(string csv_name);

int Create_Type();
void Input_Class(string year_name, string class_name);

////Create Class option 1//

paths Import_Class(string file, string year_name);
string Year_Selection(string folder);
string Create_Directory(string folder, string year_name);
string File_Import(string folder);

////Create Class option 2//

bool Duplicated_Class(string year_name, string check);
string Department_Name(int depart,int system); 
string Create_Class_Single(string year_name);

////Delete Class(es)//
void Class_Delete(string year_path, int quanti);
void Class_Clear(string year_path);

//Delete directory
void Delete_Directory(string dir);

//Class Proccession
bool Class_Proc_Active(string year_name, int option);

////Classes displaying//
int Classes_Display(string year_path);






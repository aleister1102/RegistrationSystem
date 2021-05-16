#include "MainSource.h"
bool File_Exist(string path);
////Year Creation//
void Input_Years(string store, string year_path);
string Path_ToYear(string s);
string Year_ToPath(int begin, int end);
void Create_Year(int year);

////Year Deletion//
void Year_Delete(int quanti);
void Year_Clear(string years);

////Year Proccession//
bool Year_Proc(int option, int limited_year);

////Year Displaying//
int Years_Display();


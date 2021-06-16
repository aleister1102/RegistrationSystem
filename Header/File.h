#include "MainSource.h"
bool File_Exist(string path);
void File_Create(string file_path);
void File_Clear(string file_path);
void File_YearSort(string file_path);
names File_to_NameList(string path);
void Save_ToCSV(string store, string name);
void Save_ToCSVLine(string store, string linename,string newname);
void Directory_Delete(string dir);
void Directory_Create(string dir);
string Browse_and_CreateFolder(string store, string folder,string name);
bool Name_InFile(string store, string name);
string File_Import(string folder);
int Count_line(string path);


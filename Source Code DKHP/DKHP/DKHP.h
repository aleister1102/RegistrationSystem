#include"MainSource.h"
#include"File.h"
#include"Menu.h"
#include"Convert.h"
//
void removeHead(names& l);

void removeTail(names& l);

void removeNode(names& l, name* pDel);
//

bool File_Exist1(string path);

int Count_line(string path);

string* Copy_from_file(string path);

string* Split_String_4(string name);

int* Ses(string s);

bool Name_InFile1(string store, string name);

void Input(SV& sv);

int DKHP_Dis(SV sv);

bool DKHP_Proc(int option, SV sv);

int DHKP_MenuMainDis(SV sv);

void View_List(SV sv);

names File_to_SL(string path);

int Delete_a_course_Dis(SV sv);

bool Delete_a_course_Proc(SV sv, int option);

bool DKHP_MenuMainProc(int option, SV sv);

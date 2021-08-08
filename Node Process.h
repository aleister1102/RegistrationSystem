#include "MainSource.h"

paths Init_List();
path* Create_Node(string path);
void Add_Last(paths& list, path* node);
bool Output_List(paths l);
void Remove_Info(paths& list, string path);
void SortAscen_List(paths& list);
void ReInput_fromList(string store, paths list);
paths Import_Class(string file, string year_name);


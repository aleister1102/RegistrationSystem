#include "MainSource.h"
////Initialize//
names Init_List();
name* Create_Node(string path);
////Operation//
void Add_Last(names& list, name* node);
bool Output_List(names l);
void SortAscen_YearList(names& list);
void ReInput_fromList(string store, names list);
void removeHead(names& l);
void removeTail(names& l);
void removeNode(names& l, name* pDel);

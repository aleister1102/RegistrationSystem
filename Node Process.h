#pragma once
#include "Year.h"
#include "Menu.h"

struct yr {
	string path;
	yr* next;
};
struct yrs {
	yr* head;
	yr* tail;
};

yrs Init_List();
yr* Init_Node(string path);
void Add_Last(yrs& list, yr* node);
bool Output_List(yrs l);
void Remove_Info(yrs& list, string path);
void SortAscen_List(yrs& list);

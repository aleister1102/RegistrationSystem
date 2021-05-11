#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include "Node Process.h"
#include <direct.h>
#include <filesystem>
#include <sstream>


bool File_Exist(string path);

////Year Creation//
void Input_Years(string store, string year_path);
string Path_ToYear(string s);
string Year_ToPath(int begin, int end);
string Create_Year(int time);

////Year Deletion//
void Year_Delete(int quanti);
void Year_Clear(string years);

////Year Sorting//
void Year_Sort();

////Year Displaying//
int Years_Display();


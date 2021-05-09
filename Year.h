#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include <sstream>
#include <fstream>


////Creating year section//
void Input_Years(string store, string path);
string Path_ToYear(string s);
string Year_ToPath(int begin, int end);
string Create_Year(int time);

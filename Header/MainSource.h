#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <direct.h>
#include <filesystem>
#include <sstream>
using namespace std;
namespace fs = std::experimental::filesystem;
struct date {
    int day, month, year;
};
struct user {
    string username;
    string password;
};
struct name {
	string info;
	name* next;
};
struct names {
	name* head;
	name* tail;
};
struct course {
	int id;
	string name;
	string teacher;
	int cre;
	int capacity;
	int day;
	int session;
};
struct SV {
	string name, faculty;
	int id;
};


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
struct Course {
	int id;
	string name;
	string teacher;
	int cre;
	int capacity;
	int day;
	int session;
};
struct Student {
	int Number;
	int ID;
	string name,gender, faculty;
	date birthdate;
	int socialID;
};
struct Student_node{
	Student info;
	Student_node*next;
};
struct Class{
	Student_node* head;
	Student_node* tail;
};


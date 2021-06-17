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
struct Account {
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
	int number;
	int id;
	string name, gender, faculty, birthdate;
	int socialID;
	Account user;
};
struct Student_node{
	Student info;
	Student_node*next;
};
struct Class{
	Student_node* head;
	Student_node* tail;
};


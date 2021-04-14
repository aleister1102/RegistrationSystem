#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

//Main menu
int Main_Menu_Disp();
bool Main_Menu_Proc(int option);
//Sub menu
bool Login_Proc(int option);
int Login_Disp();
void ForgotPass_Proc(int option);
int ForgotPass_Disp();
void AboutUs();

//Admin
int Admin_Disp();
bool Admin_Proc(int option);
//Student
int Student_Disp();


//Year menu
int Year_Menu_Disp();
bool Year_Proc_Active(int option);
//Class menu
int Class_Menu_Disp();
//Semester menu
int Semester_Menu_Disp();


int Valid_Data(int limit);

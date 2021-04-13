#pragma once
#include <iostream>
using namespace std;

//Main menu
int Main_Menu_Disp();
bool Main_Menu_Proc(int n);
//Sub menu
void Login_Proc(int n);
int Login_Disp();
void ForgotPass_Proc(int n);
int ForgotPass_Disp();
void AboutUs();

int Valid_Data();

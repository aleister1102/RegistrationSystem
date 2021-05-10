#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
using namespace std;
// check day 
bool check_leap_year(int y);
int day_in_month(int m, int y);
bool check_dmy(int d, int m, int y);
void enter_dmy(int& d, int& m, int& y);
// check option
int Valid_Data(int limit);
// passworwd procces
int enterpass();
void showpass(string& pass);
void hidepass(string& pass);
bool enterpass_proc(int option, string& psw);
bool enter_acc(string& usr, string& psw);
// count line in file csv
int count_acc_in_csv(string name);
// create account
string account(string usr, string psw);
// check account



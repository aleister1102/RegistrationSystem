#include "MainSource.h"

using namespace std;

// Checking
bool check_leap_year(int year);
int day_of_month(int month, int year);
bool check_dmy(date dmy);
void enter_dmy(date& dmy);
// Check option
int Valid_Data(int limit);
// Data proccess
int enterpass();
void showpass(string& pass);
void hidepass(string& pass);
bool enterpass_proc(int option, string& psw);
bool enter_acc(user& info);
int count_acc(string name);
string account(user info);

// Login
bool check_acc_ad(user info);
bool login_as_admin(user& info, date& dmy);
bool check_acc_student(user info);
bool login_as_student(user& info, date& dmy);



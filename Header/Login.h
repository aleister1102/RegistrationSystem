#include "MainSource.h"

// Date 
bool check_leap_year(int year);
int day_of_month(int month, int year);
bool check_dmy(date dmy);
void enter_dmy(date& dmy);
// Check option
int Valid_Data(int limit);
// Data proccess
int pass_mode();
void enter_data(string& param);
void enter_showpass(user &info);
void enter_hidepass(user& info);
bool pass_mode_proc(int option, user &info);
bool enter_acc(user& info);
int count_acc(string name);
string account(user info);
// Login
bool check_acc_ad(user info);
bool login_as_admin(user& info);
bool check_acc_student(user info);
bool login_as_student(user& info);



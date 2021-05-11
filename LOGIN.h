#include "MainSource.h"
#include "Menu.h"
using namespace std;
struct date{
    int d,m,y;
};
struct user {
    string username;
    string password;
};
// check day
bool check_leap_year(int y);
int day_in_month(int m, int y);
bool check_dmy(date dmy);
void enter_dmy(date& dmy);
// check option
int Valid_Data(int limit);
// password proccess
int enterpass();
void showpass(string& pass);
void hidepass(string& pass);
bool enterpass_proc(int option, string& psw);
bool enter_acc(user& info);
// count line in file csv
int count_acc_in_csv(string name);
// create account
string account(user info);
// check account

//Login as ad
bool check_acc_ad(user info);
bool login_as_admin(user& info, date& dmy);
//Login as stu
bool check_acc_student(string usr, string psw);
bool login_as_student(string& user, string& pass,date& dmy);



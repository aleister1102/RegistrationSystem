#include"MainSource.h"

bool forgotpass();
bool compare(string s1, string s2);
void split_string(string s, string& s1, string& s2);
void enter_usrname(string& name);
bool check_usrname(string name, string pathfile, int& count);
bool check_pass(string pass,int count);
bool check_key(string key, int count);
void ReInput_Account(paths list);
void change_pass_in_file(string name, string pass);
bool check_newpass(string pass);
bool Change_pass();

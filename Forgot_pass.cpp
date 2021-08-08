#include"Forgot_pass.h"
#include"Node Process.h"
#include"LOGIN.h"
void split_string(string s, string& s1, string& s2)
{
	int k = 0;
	int j = 0;
	int n = size(s);
	for (int i = 0; i < n; i++)
	{
		if ((s[i] != ',') && (k == 0))
		{
			s1 += s[i];
			if (s[i + 1] == ',')
			{
				i++;
				k = 1;
			}
		}
		else if ((s[i] != ',') && (k == 1))
		{
			s2 += s[i];
		}
	}
}
void enter_usrname(string& name)
{
	getline(cin, name);
}
bool check_usrname(string name, string pathfile,int &count)
{
	ifstream file;
	file.open(pathfile.c_str());
	while (!file.eof())
	{
		count++;
		string f,usr,psw;
		file >> f;
		split_string(f, usr, psw);
		if (compare(usr, name) == true)
		{
			return true;
			break;
		}
	}
	file.close();
	return false;
}
bool check_pass(string pass,int count)
{
	fstream f;
	int k = 0;
	f.open("acc_ad.csv", ios::in | ios::out);
	while (!f.eof())
	{
		k++;
		string nf,usr,psw;
		getline(f,nf);
		split_string(nf, usr, psw);
		if (compare(psw,pass)==true && (k == count))
		{
			return true;
		}
	}
	f.close();
	return false;
}
bool check_key(string key,int count)
{
	ifstream f;
	int k = 0;
	f.open("key.csv");
	while (!f.eof())
	{
		k++;
		string f1;
		f >> f1;
		if (compare(key, f1) == true && k == count)
		{
			return true;
			break;
		}
	}
	f.close();
	return false;
}
void ReInput_Account(paths list)
{
	path* move = list.head;
	fstream f("acc_ad.csv", ios::in | ios::out);
	while (move->next != nullptr)
	{
		f << move->info << endl;
		move = move->next;
	}
	f.close();
}
void change_pass_in_file(string name, string pass)
{
	paths list;
	fstream f;
	int k = 0;
	list = Init_List();
	string user_path = "acc_ad.csv";
	f.open(user_path.c_str(), ios::in | ios::out);
	while (!f.eof())
	{
		string f1;
		f >> f1;
		//
		string usr = "", psw = "";
		if (k == 0)
		{
			split_string(f1, usr, psw);
			//
			psw = "";
			if (compare(usr,name) == true)
			{
				f1 = "";
				int n = size(pass);
				for (int i = 0; i < n; i++)
				{
					psw += pass[i];
				}
				f1 = name + "," + psw;
				k = 1;
			}
		}
		path* n1 = new path;
		n1 = Create_Node(f1);
		Add_Last(list, n1);
	}
	f.close();
	remove(user_path.c_str());
	f.open(user_path.c_str(), ios::out);
	ReInput_Account(list);
	cout << "\t\t New password has been updated !!!" << endl;
}
bool forgotpass()
{
	string name;
	int c = 0;
	string pf = "acc_ad.csv";
	do {
		name = "";
		c = 0;
		cout << "\t\t Enter your username: ";
		enter_usrname(name);
	}while(check_usrname(name,pf,c)!=true);
	string key;
	do {
		key = "";
		cout << "\t\t Enter your key to password retrieval: ";
		enter_usrname(key);
	} while (check_key(key, c)!=true);
	string pass;
	cout << "\t\t Enter new password: ";
	enter_usrname(pass);
	change_pass_in_file(name, pass);
	return true;
}
bool check_newpass(string pass)
{
	string newpassag = "";
	cout << "\t\t Enter new password again: ";
	enter_usrname(newpassag);
	if (compare(pass,newpassag) == true)
	{
		return true;
	}
	return false;
}
bool Change_pass()
{
	string name="",pass="";
	string path = "acc_sv.csv";
 	int count = 0;
	do
	{
		count = 0; name = "";
		cout << "\t\t Enter username: ";
		enter_usrname(name);
	} while (check_usrname(name, path, count) != true);
	do
	{
		pass = "";
		cout << "\t\t Enter old password: ";
		enter_usrname(pass);
	} while (check_pass(pass,count) != true);
	string newpass;
	do {
		newpass = "";
		cout << "\t\t Enter new password: ";
		enter_usrname(newpass);
	} while (check_newpass(newpass) != true);

	change_pass_in_file(name, newpass);
	return true;
}

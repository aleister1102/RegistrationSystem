#include"DKHP.h"
#include"Node Process.h"

// Các tính năng của DSLK
void removeHead(names& l)
{
	name* p = l.head;
	l.head = p->next;
	p->next = nullptr;
	delete p;
	p = nullptr;
}

void removeTail(names& l)
{
	name* p = l.head;
	name* pDel = l.tail;
	while (p->next->next != nullptr)
	{
		p = p->next;
	}
	l.tail = p;
	p->next = nullptr;
	delete pDel;
	pDel = nullptr;
}

void removeNode(names& l, name* pDel)
{
	if (pDel == l.head)
	{
		removeHead(l);
	}
	else if (pDel == l.tail)
	{
		removeTail(l);
	}
	else
	{
		name* n1 = l.head;
		while (n1->next != pDel)
		{
			n1 = n1->next;
		}
		n1->next = pDel->next;
		pDel->next = nullptr;
		delete pDel;
		pDel = nullptr;
	}
}
// Kiểm tra file đã tồn tại hay chưa(Không out ra)
bool File_Exist1(string path)
{
	fstream fileInput(path);
	if (fileInput.fail()) {
		//cout << "\t\t File does not exist" << endl;
		return false;
	}
	else {
		//cout << "\t\t File exists" << endl;
		return true;
	}
	fileInput.close();
}
//Đếm số dòng trong file
int Count_line(string path)
{
	ifstream f;
	f.open(path);
	int c = 0;
	while (!f.eof())
	{
		string s1 = "";
		getline(f,s1);
		c++;
	}
	f.close();
	return c - 1;
}
// Lưu các dòng trong file thành một mảng kiểu string
string* Copy_from_file(string path)
{
	int n = Count_line(path);
	fstream file;
	file.open(path);
	string* s = new string[n + 1];
	int i = 0;
	while (!file.eof())
	{
		string s1;
		getline(file, s1);
		s[i++] = s1;
	}
	file.close();
	return s;
}
//Cắt chuỗi
string* Split_String_4(string name)
{
	string* s = new string[4 + 1];
	int k = 0;
	string s1, s2, s3, s4;
	for (int i = 0; i < size(name); i++)
	{
		if (k == 0 && name[i] != '_')
		{
			s1 += name[i];
			if (name[i + 1] == '_')
			{
				i++;
				k = 1;
			}
		}
		else if (k == 1 && name[i] != '_')
		{
			s2 += name[i];
			if (name[i + 1] == '_')
			{
				i++;
				k = 2;
			}
		}
		else if (k == 2 && name[i] != '_')
		{
			s3 += name[i];
			if (name[i + 1] == '_')
			{
				i++;
				k = 3;
			}
		}
		else {
			s4 += name[i];
		}
	}
	s[0] = s1;
	s[1] = s2;
	s[2] = s3;
	s[3] = s4;
	return s;
}

int* Ses(string s)
{
	int* num = new int[2];
	int k = 0;
	for (int i = 0; i < size(s); i++)
	{
		if (s[i] == 'S' || s[i] == ' ')
		{
			continue;
		}
		else
		{
			if (s[i] == '1')
			{
				num[k++] = 1;
			}
			else if (s[i] == '2')
			{
				num[k++] = 2;
			}
			else if (s[i] == '3')
			{
				num[k++] = 3;
			}
			else if (s[i] == '4')
			{
				num[k++] = 4;
			}
		}
	}
	if (size(s) == 1)
	{
		num[1] = num[0];
	}
	return num;
}

bool Name_InFile1(string store, string name)
{
	fstream f;
	f.open(store.c_str(), ios::in);
	int n = Count_line(store);
	int k = 0;
	while (!f.eof())
	{
		string read;
		getline(f,read);
		string* s1 = Split_String_4(read);
		string* s2 = Split_String_4(name);
		if (s1[0] == s2[0])
		{
			cout << "\t\tThis course has been enrolled" << endl;
			return true;
			break;
		} 
		else
		{
			if (s1[1] != s2[1])
			{
				k++;
			}
			else
			{
				int* a = Ses(s1[2]);
				int* b = Ses(s2[2]);
				if (b[0] <= a[1] && b[0] >= a[0])
				{
					cout << "\t\tConflicted with existing enrolled course sessions" << endl;
					return true;
				}
				else if (b[1] <= a[1] && b[1] >= a[0])
				{
					cout << "\t\tConflicted with existing enrolled course sessions" << endl;
					return true;
				}
			}
			if (k == n)
			{
				return false;
			}
		}
	}
	f.close();
	return false;
}

void Input(SV& sv)
{
	cout << "Enter your Faculty: ";
	getline(cin, sv.fal);
	cout << "Enter your name: ";
	getline(cin, sv.name);
	cout << "Enter your ID: ";
	cin >> sv.id;
	string folder = ".\\Register for the course\\";
	string filename = Int_ToString(sv.id) + "_" + sv.name;
	string path = Make_Path(folder, filename);
	if (!File_Exist1(path))
	{
		File_Create(path);
	}
}
int DKHP_Dis(SV sv)
{
	string fa = ".\\" + sv.fal + "\\";
	string* Sub = Copy_from_file(fa + "Courses.csv");
	int n = Count_line(fa + "Courses.csv");
	string* ID = Copy_from_file(fa + "ID.csv");
	string* Credits = Copy_from_file(fa + "Number of credits.csv");
	string* Teacher_name = Copy_from_file(fa + "Teacher name.csv");
	string* Day = Copy_from_file(fa + "Day.csv");
	string* Session = Copy_from_file(fa + "Session.csv");
	cout << "\t\t\tList of courses (ID - Name of courses - Number of credits - Teacher name - Day - Session - Student in courses)" << endl;
	for (int i = 0; i < n; i++)
	{	
		string path = fa + ".\\List of courses\\" + Sub[i] +"_"+ Teacher_name[i] + ".csv";
		if (!File_Exist1(path))
		{
			File_Create(path);
		}
		int c = Count_line(path);
		cout << "\t\t" << i + 1 << ". " << ID[i] << " - " << Sub[i] << " - " << Credits[i] << " - " << Teacher_name[i] << " - " << Day[i] << " - " << Session[i] << " - " << c << "/50" << endl;
	}
	cout << "\t\t" << n + 1 << ". Exit" << endl;
	cout << "\t\tYour choice is : ";
	return Valid_Data(n + 1);
}
bool DKHP_Proc(int option, SV sv)
{
	string fa = ".\\" + sv.fal + "\\";
	int n = Count_line(fa + "Courses.csv");
	if (option == n + 1)
	{
		return false;
	}
	else {
		string* Sub = Copy_from_file(fa + "Courses.csv");
		string* ID = Copy_from_file(fa + "ID.csv");
		string* Credits = Copy_from_file(fa + "Number of credits.csv");
		string* Teacher_name = Copy_from_file(fa + "Teacher name.csv");
		string* Day = Copy_from_file(fa + "Day.csv");
		string* Session = Copy_from_file(fa + "Session.csv");
		//
		string folder = ".\\Register for the course\\";
		string filename = Int_ToString(sv.id) + "_" + sv.name;
		string path = Make_Path(folder, filename);

		int k = Count_line(path);
		//
		string path1 = fa + ".\\List of courses\\" + Sub[option - 1] + "_" + Teacher_name[option - 1] + ".csv";
		int k1 = Count_line(path1);
		string sub = Sub[option - 1] + "_" + Day[option - 1] + "_" + Session[option - 1]+"_"+Teacher_name[option-1];
		//
		if (k < 5)
		{
			if (k1 < 50)
			{
				if (Name_InFile1(path, sub) == false)
				{
					Save_ToCSV(path, sub);
					Save_ToCSV(path1, Int_ToString(sv.id) + "_" + sv.name);
					cout << "\t\tEnroll for the course successfully" << endl;
					return true;
				}
			}
			else
			{
				cout << "\t\tThe course is full !!!" << endl;
				return true;
			}
		}
		else
		{
			cout << "\t\tThe maximum number of courses that can be enrolled has been reached !!!" << endl;
			system("pause");
			return false;
		}
		return true;
	}
}

int DHKP_MenuMainDis(SV sv)
{
	cout << "\t\t\t----Menu of DKHP----" << endl;
	cout << "\t\t1. DKHP" << endl;
	cout << "\t\t2. View list of courses have been enrolled" << endl;
	cout << "\t\t3. Delete a course from enrolled list" << endl;
	cout << "\t\t4. Exit" << endl;
	cout << "\t\tYour choice is: ";
	return Valid_Data(4);
}

void View_List(SV sv)
{
	cout << "\t\t\tList of enrolled courses" << endl;
	string folder = ".\\Register for the course\\";
	string filename = Int_ToString(sv.id) + "_" + sv.name;
	string path = Make_Path(folder, filename);
	int n = Count_line(path);
	ifstream f;
	f.open(path);
	int i = 0;
	while (!f.eof())
	{
		i++;
		if (i <= n)
		{
			string f1;
			getline(f, f1);
			cout << "\t\t" << i << ". " << f1 << endl;
		}
		else break;
	}
	f.close();
}

names File_to_SL(string path)
{
	names l = Init_List();
	ifstream f;
	f.open(path);
	while (!f.eof())
	{
		string f1;
		getline(f, f1);
		name* p = Create_Node(f1);
		Add_Last(l, p);
	}
	f.close();
	return l;
}

int Delete_a_course_Dis(SV sv)
{
	string folder = ".\\Register for the course\\";
	string filename = Int_ToString(sv.id) + "_" + sv.name;
	string path = Make_Path(folder, filename);
	View_List(sv);
	cout<<"\t\t"<<Count_line(path)+1<<". Exit"<<endl;
	cout << "\t\tYour choice is: ";
	return Valid_Data(Count_line(path)+1);
}

bool Delete_a_course_Proc(SV sv,int option)
{
	string folder = ".\\Register for the course\\";
	string filename = Int_ToString(sv.id) + "_" + sv.name;
	string path = Make_Path(folder, filename);
	names list = File_to_SL(path);
	if (option == Count_line(path) + 1)
	{
		return false;
	}
	else
	{
		// Xóa môn học khỏi file sinh viên

		int c = 0;
		name* p = list.head;
		while (p != NULL)
		{
			c++;
			if (c == option)
			{
				break;
			}
			p = p->next;
		}
		name* pDEl = p;
		string s = pDEl->info;
		removeNode(list, pDEl);
		File_Clear(path);
		File_Create(path);
		ReInput_fromList(path, list);
		
		//Xóa tên sinh viên khỏi file môn học

		string* s1 = Split_String_4(s);
		string fa = ".\\" + sv.fal + "\\";
		string path1 = fa+".\\List of courses\\" + s1[0]+"_"+ s1[3] + ".csv";
		names list1 = File_to_SL(path1);
		name* n1 = list1.head;
		while (n1 != NULL)
		{
			string ss = Int_ToString(sv.id) + "_" + sv.name;
			if (n1->info == ss)
			{
				break;
			}
			n1 = n1->next;
		}
		removeNode(list1, n1);
		File_Clear(path1);
		File_Create(path1);
		ReInput_fromList(path1, list1);
		return true;
	}
}

bool DKHP_MenuMainProc(int option, SV sv)
{
	if (option == 1)
	{
		bool run = true;
		while (run)
		{
			run = DKHP_Proc(DKHP_Dis(sv), sv);
		}
		return true;
	}
	else if (option == 2)
	{
		View_List(sv);
		system("pause");
		return true;
	}
	else if (option == 3)
	{
		bool run = true;
		while (run)
		{
			run = Delete_a_course_Proc(sv, Delete_a_course_Dis(sv));
		}
		return true;
	}
	else return false;
}
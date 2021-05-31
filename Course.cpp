#include "Course.h"
#include "Class.h"
#include "Year.h"
#include "Menu.h"
#include "File.h"
#include "Convert.h"
//-------------------Đây chỉ là Demo, chưa phải code có thể dùng--------------------------------//
//-------------------Đây chỉ là Demo, chưa phải code có thể dùng--------------------------------//
//-------------------Đây chỉ là Demo, chưa phải code có thể dùng--------------------------------//
//-------------------Đây chỉ là Demo, chưa phải code có thể dùng--------------------------------//
//-------------------Đây chỉ là Demo, chưa phải code có thể dùng--------------------------------//
bool Valid_Course(course c)
{
	if (c.id < 0 || c.cre < 0 || c.capacity < 0 || c.day<0 || c.session <0 )
	{
			return false;
	}
	return true;
}
void Create_Course()
{
	course new_course;
	string course_name;
	string course_path;
	FILE* file;
	do {
		cout << "\t\t ID: "; new_course.id = Valid_Data(100);
		cout << "\t\t Course Name: "; getline(cin, new_course.name); 
		cout << "\t\t Teacher Name: "; getline(cin, new_course.teacher);
		cout << "\t\t Number of credits: "; cin >> new_course.cre;
		cout << "\t\t Maximum students: "; cin >> new_course.capacity;
		cout << "\t\t Day of the week: " << endl;
		cout << "\t\t Monday \t- 1" << endl;
		cout << "\t\t Tuesday \t- 2" << endl;
		cout << "\t\t Wednesday \t- 3" << endl;
		cout << "\t\t Thursday \t- 4" << endl;
		cout << "\t\t Friday \t- 5" << endl;
		cout << "\t\t Saturday \t- 6" << endl;
		cout << "\t\t Select day: ";
		cin >> new_course.day;
		cout << "\t\t Session: " << endl;
		cout << "\t\t S1 (07:30) - 1" << endl;
		cout << "\t\t S2 (09:30) - 2" << endl;
		cout << "\t\t S3 (13:30) - 3" << endl;
		cout << "\t\t S4 (15:30) - 4" << endl;
		cout << "\t\t Select session: ";
		cin >> new_course.session;
		course_name = Int_ToString(new_course.id) + new_course.name + ".txt";
		course_path = ".\\Semester\\" + course_name;
	} while (Valid_Course(new_course) != true || File_Exist(course_path)==true);

	file = fopen(course_path.c_str(), "a+");
	fclose(file);
}

bool Course_Proc(int option)
{
	if (option == 1)
	{
		Create_Course();
		system("cls");
		return true;
	}
	else
	{
		system("cls");
		return false;
	}
}

#include "Header\Date.h"
#include "Header\Semester.h"
#include "Header\Convert.h"
void output_dmy(date dmy)
{
	cout<<dmy.day<<"/"<<dmy.month<<"/"<<dmy.year;
}

//*Kiểm tra năm nhuận
bool check_leap_year(int year)
{
	return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
}
//*Số ngày của tháng
int day_of_month(int month, int year)
{
	switch (month)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12:	return 31;
	case 4:case 6:case 9:case 11: return 30;
	default:
		if (check_leap_year(year))
		{
			return 29;
		}
		else return 28;
		break;
	}
}
//*Kiểm tra tính hợp lệ của ngày tháng
bool check_dmy(date dmy)
{
	if (dmy.year <= 0 || dmy.month <= 0)
	{
		return false;
	}
	if (dmy.month < 1 || dmy.month>12)
	{
		return false;
	}
	if (dmy.day <= 0 || dmy.day > day_of_month(dmy.month, dmy.year))
	{
		return false;
	}
	return true;
}
//*Nhập ngày tháng
void enter_dmy(date& dmy)
{
	do {
		cout << "\t\t Enter day / month / year: " << endl;
		cout << "\t\t ";
		cin >> dmy.day; cout << "\t\t ";
		cin >> dmy.month; cout << "\t\t ";
		cin >> dmy.year;
		cin.ignore();
	} while (check_dmy(dmy) != true);
	
}
bool check_registration_date(date dmy)
{
	if(dmy.month == 9){
		if(dmy.day>=1 && dmy.day <=14)
		{
			return true;
		}
	}
	else if(dmy.month==12 ||dmy.month==4)
	{
		if(dmy.day>=16 && dmy.day<=26)
		{
			return true;
		}
	}
	return false;
}

//*Kiểm tra khoảng ngày có bị trùng hay không
//@param timeline[3] Mảng 3 mùa @param dmy Khoảng cần check @param index Chỉ số mùa cần check
//@return True nếu trùng khoảng
bool check_duplicated_range(TimeRange semTime[3], TimeRange dmy, int index)
{
	for (int i = 0; i < 3; i++)
	{
		int begin = semTime[i].begin.month;
		int end = semTime[i].end.month;
		if (begin != 0 && end != 0)
		{
			if ((dmy.begin.month < begin && dmy.end.month < begin) || (dmy.begin.month > end && dmy.end.month > end))
			{
				return false; //Duplicated range
			}
		}
	}
	return true;
}
//*Nhập thời gian của học kỳ
void enter_MonthRange(TimeRange semTime[3], int index)
{
	TimeRange dmy;
	do
	{
		if (index == 0)
		{
			cout << "Autumn will from : ";
		}
		else if (index == 1)
		{
			cout << "Spring will from : ";
		}
		else
		{
			cout << "Summer will from : ";
		}
		cin >> dmy.begin.month;
		cout << "to: ";
		cin >> dmy.end.month;
	} while (check_duplicated_range(semTime, dmy, index) || (dmy.begin.month>dmy.end.month));
	semTime[index] = dmy;
}
//*Nhập thời gian của các học kỳ
void enter_SemesterTime(TimeRange semTime[3],date dmy)
{
	for (int i = 0; i < 3; i++)
	{
		//Nhập tháng
		enter_MonthRange(semTime, i);
		do{
			//Nhập ngày cho các tháng giới hạn
			cout << "Month " << semTime[i].begin.month << " start at day: ";
			cin >> semTime[i].begin.day;
			cout << "Month " << semTime[i].end.month << " end at day: ";
			cin >> semTime[i].end.day;
			//Gán năm
			semTime[i].begin.year = dmy.year;
			semTime[i].end.year = dmy.year;
		}while(check_dmy(semTime[i].begin)!=true || check_dmy(semTime[i].end)!=true);
	}
}
//*Khởi tạo thời gian trong năm
void init_SemesterTime(TimeRange semTime[3])
{
	//Cho mảng bằng -1 để so sánh với các ngày đã trùng
	semTime[0].begin.month = semTime[0].end.month = -1;
	for (int i = 1; i < 3; i++)
	{
		semTime[i].begin.month = semTime[i].end.month = 0;
	}
}
//*Nhập thời đkhp đơn lẻ
void enter_RegistTime(string semester_path, TimeRange &dmy)
{
	ifstream f(semester_path);
	string reader;
	getline(f, reader);
	date begin = String_ToDate(reader);
	//Gán cùng tháng cùng năm
	dmy.begin.month = dmy.end.month = begin.month;
	dmy.begin.year = dmy.end.year = begin.year;
	//Nhập ngày của đkhp
	do{
	cout<<"Registration start at: ";
	cin>>dmy.begin.day;
	cout<<"end at: ";
	cin>>dmy.end.day;
	}while(check_dmy(dmy.begin)!=true||check_dmy(dmy.end)!=true || dmy.begin.day>=dmy.end.day);
}
//*Nhập thời gian đăng ký học phần cho cả năm
void enter_RegsTime(TimeRange regtime[3],string seasons[3])
{
	for(int i=0; i < 3; i++)
	{
		View_Semester_Time(seasons[i]);
		enter_RegistTime(seasons[i], regtime[i]);
	}
}
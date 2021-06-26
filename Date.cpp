#include "Header\Date.h"
void output_dmy(date dmy)
{
	cout<<dmy.day<<"/"<<dmy.month<<"/"<<dmy.year;
}

//Kiểm tra năm nhuận
bool check_leap_year(int year)
{
	return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
}
//Số ngày của tháng
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
//Kiểm tra tính hợp lệ của ngày tháng
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
//Nhập ngày tháng
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

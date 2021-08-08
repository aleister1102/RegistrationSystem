#include "Node Process.h"
#include "Semester.h"
#include "Convert.h"

//Kiểm tra danh sách liên kết rỗng
//Param: một DSLK
//Return: true nếu list rỗng, false nếu list có phần tử
bool CheckEmpty(names list)
{
	if (list.head == nullptr)
		return true;
	return false;
}
//Khởi tạo danh sách liên kết
//Return: danh sách liên kết đã khởi tạo
names Init_List()
{
	names l;
	l.head = nullptr;
	l.tail = nullptr;
	return l;
}
//Khởi tạo node
//Param: thông tin của node, ở đây là một chuỗi chứa tên
//Return: con trỏ node chứa name
name* Create_Node(string info)
{
	name* s = new name;
	s->info = info;
	s->next = nullptr;
	return s;
}
//Thêm node vào cuối list
//Param: một danh sách chứa name, một con trỏ trỏ đến stuct name
void Add_Last(names& list, name* node)
{
	if (CheckEmpty(list))
	{
		list.head = node;
		list.tail = node;
	}
	else
	{
		list.tail->next = node;
		list.tail = node;
	}
}
//Sao chép thông tin danh sách liên kết sang một danh sách khác không cùng địa chỉ
//Param: một list name
//Return: một list name khác đã copy
names Copy_List(names l)
{
	name* move = l.head;
	names temp = Init_List();
	while (move != nullptr)
	{
		name* add = Create_Node({ move->info });
		Add_Last(temp, add);
		move = move->next;
	}
	return temp;
}
//Truyền thông tin từ list vào file
//Param: file cần truyển thông tin, danh sách liên kết chứa thông tin
void ReInput_fromList(string store, names list)
{
	name* move = list.head;
	fstream f(store, ios::in | ios::out);
	while (move->next != nullptr)
	{
		if (Name_InFile(store, move->info) == true)
		{
			return;
		}
		f << move->info << endl;
		move = move->next;
	}
	f.close();
}
//Sắp xếp tăng dần cho năm
//Param: DSLK chứa tên năm cần sort
void SortAscen_YearList(names & list)
{
	//Create new list with different address
	names result = Copy_List(list);
	name * curr = result.head;

	name* move = list.head;
	//Create flags
	int min;
	int before = 0;

	while (curr != nullptr)
	{
		min = 100000;
		//Set up the flag of smallest number
		while (move != nullptr)
		{
			int num = Year_ToInt(move->info);
			if (num < min && num> before)
			{
				min = num;
			}
			move = move->next;
		}
		//Reset pointer
		move = list.head;
		bool check = false;
		//Compare node with flag and copy to new list
		while (move != nullptr)
		{
			int num = Year_ToInt(move->info);
			if (num == min)
			{
				curr->info = move->info;
				check = true;
				curr = curr->next;
			}

			move = move->next;
		}
		move = list.head;
		before = min;
		if (check == false) { curr = curr->next; }
	}
	list = result;
}
//Xuất danh sách liên kết
//Param: list
//Return: trả về false nếu danh sách rỗng
bool Output_List(names l)
{
	if (CheckEmpty(l))
	{
		cout << "Empty List !!" << endl;
		return false;
	}

	cout << "List of Node: " << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	name* move = l.head;
	int count = 1;
	while (move->next != nullptr)
	{
		cout << "\tThe " << count++ << " object: ";
		cout << move->info << " " << endl;
		move = move->next;
	}
	return true;
}

#include "Node Process.h"

bool CheckEmpty(paths list)
{
	if (list.head == nullptr)
		return true;
	return false;
}

paths Init_List()
{
	paths l;
	l.head = nullptr;
	l.tail = nullptr;
	return l;
}

path* Create_Node(string info)
{
	path* s = new path;
	s->info = info;
	s->next = nullptr;
	return s;
}

void Add_Last(paths& list, path* node)
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
void Remove_Info(paths& list, string info)
{
	path* move = list.head;
	if (move->info == info)
	{
		path* temp = move;
		list.head = list.head->next;
		delete temp;
		return;
	}
	while (move->next->next != nullptr)
	{
		if (move->next->info == info)
		{
			path* temp = move;
			move->next = move->next->next;
			delete temp;
			return;
		}
		move = move->next;
	}
	if (move->next->info == info)
	{
		path* temp = move->next;
		move->next = nullptr;
		list.tail = move;
		delete temp;
		return;
	}
}
bool Output_List(paths l)
{
	if (CheckEmpty(l))
	{
		cout << "Danh sach rong" << endl;
		return false;
	}

	cout << "List of Node: " << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	path* move = l.head;
	int count = 1;
	while (move->next != nullptr)
	{
		cout << "\tThe " << count++ << " object: ";
		cout << move->info << " " << endl;
		move = move->next;
	}
	return true;
}
paths Copy_List(paths l)
{
	path* move = l.head;
	paths temp = Init_List();
	while (move != nullptr)
	{
		path* add = Create_Node({ move->info });
		Add_Last(temp, add);
		move = move->next;
	}
	return temp;
}
int Year_ToNumber(string year)
{
	stringstream ss; int n;
	ss <<  year.substr(0, 4);
	ss >> n;
	return n;
}
void SortAscen_List(paths & list)
{
	//Create new list with different address
	paths result = Copy_List(list);
	path * curr = result.head;

	path* move = list.head;
	//Create flags
	int min;
	int before = 0;

	while (curr != nullptr)
	{
		min = 100000;
		//Set up the flag of smallest number
		while (move != nullptr)
		{
			int num = Year_ToNumber(move->info);
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
			int num = Year_ToNumber(move->info);
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

#include "Node Process.h"

bool CheckEmpty(yrs list)
{
	if (list.head == nullptr)
		return true;
	return false;
}

yrs Init_List()
{
	yrs l;
	l.head = nullptr;
	l.tail = nullptr;
	return l;
}

yr* Init_Node(string path)
{
	yr* s = new yr;
	s->path = path;
	s->next = nullptr;
	return s;
}

void Add_Last(yrs& list, yr* node)
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
void Remove_Info(yrs& list, string path)
{
	yr* move = list.head;
	if (move->path == path)
	{
		yr* temp = move;
		list.head = list.head->next;
		delete temp;
		return;
	}
	while (move->next->next != nullptr)
	{
		if (move->next->path == path)
		{
			yr* temp = move;
			move->next = move->next->next;
			delete temp;
			return;
		}
		move = move->next;
	}
	if (move->next->path == path)
	{
		yr* temp = move->next;
		move->next = nullptr;
		list.tail = move;
		delete temp;
		return;
	}
}
bool Output_List(yrs l)
{
	if (CheckEmpty(l))
	{
		cout << "Danh sach rong" << endl;
		return false;
	}

	cout << "List of Students: " << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	yr* move = l.head;
	int count = 1;
	while (move != nullptr)
	{
		cout << "\tThe " << count << " year" << endl;
		cout << move->path << " ";
		move = move->next;
		count++;
	}
	return true;
}


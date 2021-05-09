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

yr* Create_Node(string info)
{
	yr* s = new yr;
	s->info = info;
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

	cout << "List of Node: " << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	yr* move = l.head;
	int count = 1;
	while (move->next != nullptr)
	{
		cout << "\tThe " << count++ << " object: ";
		cout << move->path << " " << endl;
		cout << "\tThe " << count << " object" << endl;
		cout << move->path << " ";
		move = move->next;
	}
	return true;
}
yrs Copy_List(yrs l)
{
	yr* move = l.head;
	yrs temp = Init_List();
	while (move != nullptr)
	{
		yr* add = Init_Node({ move->path });
		Add_Last(temp, add);
		move = move->next;
	}
	return temp;
}
int Create_Number(string year)
{
	stringstream ss; int n;
	ss <<  year.substr(0, 4);
	ss >> n;
	return n;
}
void SortAscen_List(yrs & list)
{
	//Create new list with different address
	yrs result = Copy_List(list);
	yr * curr = result.head;

	yr* move = list.head;
	//Create flags
	int min = Create_Number(move->path);
	int before = 0;

	while (curr != nullptr)
	{
		min = 100000;
		//Set up the flag
		while (move != nullptr)
		{
			int num = Create_Number(move->path);
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
			int num = Create_Number(move->path);
			if (num == min)
			{
				curr->path = move->path;
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

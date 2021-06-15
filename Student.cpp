#include<iostream>
#include<string>
#include<fstream>


using namespace std;


struct Student {
    string no;
    string ID;
    string firstname;
    string lastname;
    string gender;
    string date;
    string socialID;
};

struct Node {
    Student info;
    Node* next;

};

struct List {
    Node* head;
    Node* tail;
};

void init(Node*& node) {
    node = new Node;
    node->next = NULL;
}

void init(List& list) {
    list.head = NULL;
    list.tail = NULL;
}

Node* createNode(Student student) {
    Node* node;

    init(node);
    node->info = student;

    return node;
}

bool isEmpty(List list) {
    if (list.head == NULL) return true;
    else return false;
}

void addTail(List& l, Node* node) {
    if (isEmpty(l)) {
        l.head = node;
        l.tail = node;
    }
    else {
        l.tail->next = node;
        l.tail = node;
    }
}

void print(List l) {
    Node* dir = l.head;
    if (!isEmpty(l)) {
        while (dir != NULL) {
            cout
                << dir->info.no
                << " "
                << dir->info.ID
                << " "
                << dir->info.firstname
                << " "
                << dir->info.lastname
                << " "
                << dir->info.gender
                << " "
                << dir->info.date
                << " "
                << dir->info.socialID
                << endl;
            dir = dir->next;
        }
    }
    else {
        cout << "Does not contain any node";
    }
}

List importfromCSV(string path) {
    List l;
    init(l);
    Node* node;

    fstream file;
    Student student;
    string line;
    file.open(path);
    if (file.fail()) {
        cout << "Cannot open file!";
        return l;
    }
    else {
        cout << "Open file successfully!" << endl;
        getline(file, line);
        int count = 1;

        while (file.good()) {

            if (count != 7) {
                getline(file, line, ',');
            }
            else getline(file, line, '\n');

            switch (count) {
            case 1:
                student.no = line;
                break;
            case 2:
                student.ID = line;
                break;
            case 3:
                student.firstname = line;
                break;
            case 4:
                student.lastname = line;
                break;
            case 5:
                student.gender = line;
                break;
            case 6:
                student.date = line;
                break;
            case 7:
                student.socialID = line;
                break;
            default:
                cout << "Error!" << endl;
                break;
            }
            if (count < 7) count++;
            else {
                count = 1;
                node = createNode(student);
                addTail(l, node);
            }
        }
        file.close();

        return l;
    }
}

//---------------------------------------//

int main() {
    List list;
    Node* node;
    init(list);
    list = importfromCSV("Students_list.csv");
    print(list);
    return 0;
}

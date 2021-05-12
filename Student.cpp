#include<iostream>
#include<string>
#include<fstream>

using namespace std;


struct Student {
    string no;
    string studentID;
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
    if (list.head == NULL) return false;
    else return true;
}

void addTail(List &l, Node* node) {
    if (isEmpty) {
        l.head = node;
        l.tail = node;
    }
    else {
        l.tail->next = node;
        l.tail = node;
    }
}


void export(List &l, string path) {
    
    Node* node;
    fstream file;
    
    file.open(path, ios::in || ios::app);
    Student student;
    string s, temp;
    while (!file.eof()) {
        
        getline(file, s);
        
        for (int i = 1; i <= 5; i++) {
            getline(s, temp, ',');    
        }
    }


}



int main() {
    

    return 0;
}
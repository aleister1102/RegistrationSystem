#include <iostream>
#include <string>
#include <fstream>
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

int main() {
    
    fstream file;
    
    file.open("Book1.csv", ios::in || ios::app);
    Student student;
    string line;
    
    getline(file, line);
    if (file.fail()) {
        cout << "Cannot find the file. Please check again.";
    }
    else {
        for (int i = 0; getline(file, line); i++) {
            string element = "";
            
            for (int j = 0; j < line.length() ;j++) {
                if (line[j] != ',') {
                    element += line[j];
                }
                else {
                    if (i == 0) {
                        student.no = element;
                    }
                    else if (i == 1) {
                        student.studentID = element;
                    }
                    else if (i == 2) {
                        student.firstname = element;
                    }
                    else if (i == 3) {
                        student.lastname = element;
                    }
                    else if (i == 4) {
                        student.gender = element;
                    }
                    else if (i == 5) {
                        student.date = element;
                    }
                    else if (i == 6) {
                        student.socialID = element;
                    }
                    element = "";
                }
            }
           
        }
    }

    cout << student.no << student.studentID << student.firstname << student.lastname << student.gender << student.date << student.socialID;
    return 0;
}
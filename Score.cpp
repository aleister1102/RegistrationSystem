#include "Header/Menu.h"
#include "Header/Class.h"
#include "Header/File.h"
#include "Header/Student.h"
#include "Header/Vector.h"
#include "Header/Convert.h"
#include "Header/Score.h"
#include "Header/Node Process.h"
//*Nhập tên môn học có bảng điểm vào hệ thống

void Score_Import()
{
    cout << "WARNING: The score file must be in the direction: .\\Students\\Students' ScoreBoard\\Import\\" << endl;
    string folder = ".\\Students\\Students' ScoreBoard\\Import\\";
    string import = File_Import(folder);
    vector<string> list = File_ToVector(import);
    string course_name = Path_ToName(import);
    File_Append(Make_Path(folder, "Import ScoreBoard"),course_name);
}
//*Xử lý và điều hướng các hàm tính năng của năm
//@param option Lựa chọn tính năng @param semester_path đường dẫn tới học kỳ
//@return True nếu cần dùng tiếp, false nếu muốn thoát ra hẳn
bool Score_Proc(int option, string semester_path)
{
    if (option == 1)
    {
        string faculty = Faculty_Name(Department_Menu_Disp(), 1);
        if (faculty == "OUT")
            return false;
        Student_Export(semester_path,faculty);
        cout<<"\t\t ";system("pause");
        return true;
    }
    else if (option == 2)
    {
        Score_Import();
        cout<<"\t\t ";system("pause");
        return true;
    }
    else if (option == 3)
    {
        Admin_ViewScoreBoard();
        cout << "\t\t "; system("pause");
        return true;
    }
    else
    {
        system("cls");
        return false;
    }
}

void Admin_ViewScoreBoard() {
    //make path
    string path = "./Students/Students' ScoreBoard/Import/Import Scoreboard.csv";
    //read file and save it to list of string
    vector<string> courses = File_ToVector(path);
    //print avalable course out, let user choose which courses
    int choice = Choose_Courses(courses);
    while (choice > courses.size() || choice < 0 || cin.fail()) {
        cout << "You don't type a number or your number is over the limit. Try again";
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }
        choice = Choose_Courses(courses);
    }
    if (choice == 0) return;
    else {
        string course = courses[size_t(choice - 1)];
        string course_file = "./Students/Students' ScoreBoard/Import/" + course;
        if (File_Exist(course_file)) {
            vector<string> list = File_ToVector(course_file);
            Score* score_list = Vector_toScore(list);
            Display_ScoreList(score_list, list.size());
        }
        else {
            cout << "Cannot find the course file." << endl;
        }
    }
}

int Choose_Courses(vector<string> courses) {
    //Display menu
    system("cls");
    cout << "\t\t0. Exit" << endl;
    Display_List(courses);
    //Input choice
    int choice = 0;
    cin >> choice;
    return choice;
}

void Display_List(vector<string> list) {
    system("cls");
    //print list
    for (int i = 0; i < list.size(); i++) {
        cout << "\t\t" << i + 1 << ".";
        cout << list[i] << endl;
    }
}

Score* init(int number) {
    Score* score_list = new Score[number];
    for (int i = 0; i < number; i++) {
        score_list[i].number = -1;
        score_list[i].id = "";
        score_list[i].total_mark = -1;
        score_list[i].final_mark = -1;
        score_list[i].midterm_mark = -1;
        score_list[i].other_mark = -1;
    }
    return score_list;
}

Score* Vector_toScore(vector<string> list) {
    Score* my_score = init(list.size());
    for (int i = 0; i < list.size(); i++) {
        string line = list[i];
        line += "\n";
        char c;
        string temp = "";
        int k = 1;
        for (int j = 0; j < line.length(); j++) {
            c = line[j];
            if (c == ',' || c == '\n') {
                switch (k) {
                    case 1: {
                        my_score[i].number = stoi(temp);
                        break;
                    }
                    case 2: {
                        my_score[i].id = temp;
                        break;
                    }
                    case 3: {
                        my_score[i].name = temp;
                        break;
                    }
                    case 4: {
                        my_score[i].total_mark = stod(temp);
                        break;
                    }
                    case 5: {
                        my_score[i].final_mark = stod(temp);
                        break;
                    }
                    case 6: {
                        my_score[i].midterm_mark = stod(temp);
                        break;
                    }
                    case 7: {
                        my_score[i].other_mark = stod(temp);
                        break;
                    }
                    default: {
                        cout << "Error!";
                        break;
                    }
                }
                k++;
                temp = "";
            }
            else {
                temp += c;
            }
        }
    }
    return my_score;
}

void Display_ScoreList(Score* score_list, int capacity) {
    cout << "No \t ID \t\t Full Name \t\t\t Total Mark \t Final Mark \t Midterm Mark \t Other Mark \t" << endl;
    for (int i = 0; i < capacity; i++) {
        cout << score_list[i].number << "\t" << score_list[i].id << "\t\t" << score_list[i].name << "\t\t\t\t" <<
            score_list[i].total_mark << "\t\t" << score_list[i].final_mark << "\t\t" << score_list[i].midterm_mark << "\t\t" <<
            score_list[i].other_mark << endl;
    }
}
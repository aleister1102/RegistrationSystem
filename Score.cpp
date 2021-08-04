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
        List_score subject_score;
        string course_file = "";
        subject_score = Admin_ViewScoreBoard(course_file);
        Display_ScoreList(subject_score);
        cout << "\t\t "; system("pause");
        return true;
    }
    else if (option == 4) {
        string course_file = "";
        Admin_UpdateScore();
        cout << "\t\t "; system("pause");
        return true;
    }
    else
    {
        system("cls");
        return false;
    }
}
//return: number of courses
List_score Admin_ViewScoreBoard(string& course_file) {
    //make path
    string path = "./Students/Students' ScoreBoard/Import/Import Scoreboard.csv";
    //read file and save it to list of string
    vector<string> courses = File_ToVector(path);
    List_score scores = init_ListScore();
    //print avalable course out, let user choose which courses
    size_t choice = Choose_Courses(courses);
    while (choice > courses.size() || choice < 0 || cin.fail()) {
        cout << "You don't type a number or your number is over the limit. Try again";
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }
        choice = Choose_Courses(courses);
    }
    if (choice != 0) {
        string course = courses[choice - 1];
        course_file = "./Students/Students' ScoreBoard/Import/" + course;
        if (File_Exist(course_file)) {
            vector<string> list = File_ToVector(course_file);
            Score* score_list = Vector_toScore(list);
            scores.capacity = list.size();
            scores.data = score_list;
        }
        else {
            cout << "Cannot find the course file." << endl;
        }
    }
    return scores;
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

void Display_ScoreList(List_score score_list) {
    if (score_list.capacity == 0) {
        return;
    }
    else {
        cout << "No \t ID \t\t Full Name \t\t\t Total Mark \t Final Mark \t Midterm Mark \t Other Mark \t" << endl;
        for (int i = 0; i < score_list.capacity; i++) {
            cout << score_list.data[i].number << "\t" << score_list.data[i].id << "\t\t" << score_list.data[i].name << "\t\t\t" <<
                setw(2) << score_list.data[i].total_mark << "\t\t" << setw(2) << score_list.data[i].final_mark << "\t\t" <<
                setw(2) << score_list.data[i].midterm_mark << "\t\t" << setw(2) << score_list.data[i].other_mark << endl;
        }
    }

}
//====================//
void Admin_UpdateScore() {
    List_score subject_score;
    string course_path = "";
    subject_score = Admin_ViewScoreBoard(course_path);
    if (subject_score.capacity == 0) {
        cout << "Nothing to change!" << endl;
    }
    else {
        cout << "The score list of subject: " << endl;
        Display_ScoreList(subject_score);
        cout << "Choose the student's no. to change her/his result. Choose 0 to exit." << endl;
        //Choose and process
        cout << "You choose: ";
        int choice = -1;
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > subject_score.capacity) {
            cin.clear();
            cin.ignore();
            cout << "You didn't choose the right number or you chose over the limit. Try again!";
            cin >> choice;
        }
        if (choice == 0) return;
        else {
            //After chosen, get the data
            Score chosen_score = subject_score.data[choice - 1];
            //Update the data
            Update_Score(chosen_score);
            cout << "Update successfully!";
            //Write to file
            string new_line = Score_toString(chosen_score);
            File_Line_Update(course_path, 1, choice, new_line);
        }
    }
}

void Input_Valid(double& num) {
    num = -1;
    cin >> num;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Invalid number. Try again!";
        cin >> num;
    }
}

void Update_Score(Score& chosen_score) {
    cout << "Type the new result." << endl;
    double input_score = -1;

    cout << "Total Mark: "; 
    Input_Valid(input_score);
    chosen_score.total_mark = input_score;

    cout << "Final Mark: "; 
    Input_Valid(input_score);
    chosen_score.final_mark = input_score;

    cout << "Midterm Mark: "; 
    Input_Valid(input_score);
    chosen_score.midterm_mark = input_score;

    cout << "Other Mark: "; 
    Input_Valid(input_score);
    chosen_score.other_mark = input_score;
}

string Score_toString(Score my_score) {
    return to_string(my_score.number) + "," + my_score.id + "," + my_score.name + "," + to_string(my_score.total_mark) + "," + to_string(my_score.final_mark) + "," + to_string(my_score.midterm_mark) + "," + to_string(my_score.other_mark);
}

//============================================//

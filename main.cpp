#include <iostream>
#include <vector>

using namespace std;

class Student {
public:
    string indexNo;
    string fullName;

    Student(string i, string n) {
        indexNo = i;
        fullName = n;
    }
};

vector<Student> studentList;

void addStudent() {
    string index, name;

    cout << "Enter index number: ";
    cin >> index;
    cin.ignore();

    cout << "Enter full name: ";
    getline(cin, name);

    studentList.push_back(Student(index, name));
    cout << "Student added.\n";
}

void viewStudents() {
    if (studentList.size() == 0) {
        cout << "No students registered.\n";
        return;
    }

    for (int i = 0; i < studentList.size(); i++) {
        cout << studentList[i].indexNo
             << " - "
             << studentList[i].fullName << endl;
    }
}

int main() {
    int option;

    do {
        cout << "\n1. Add student\n";
        cout << "2. View students\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> option;

        if (option == 1) addStudent();
        else if (option == 2) viewStudents();

    } while (option != 0);

    return 0;
}

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ================= STUDENT STRUCT =================
struct Student {
    string indexNumber;
    string fullName;
};

Student students[100];
int studentCount = 0;

// ================= WEEK 1 =================
void addStudent() {
    if (studentCount >= 100) {
        cout << "Maximum students reached.\n";
        return;
    }

    cout << "Enter index number: ";
    cin >> students[studentCount].indexNumber;
    cin.ignore();

    cout << "Enter full name: ";
    getline(cin, students[studentCount].fullName);

    studentCount++;
    cout << "Student registered successfully.\n";
}

void viewStudents() {
    if (studentCount == 0) {
        cout << "No students registered.\n";
        return;
    }

    cout << "\nRegistered Students:\n";
    for (int i = 0; i < studentCount; i++) {
        cout << students[i].indexNumber << " - "
             << students[i].fullName << endl;
    }
}

// ================= WEEK 2 =================
void createLectureSession() {
    if (studentCount == 0) {
        cout << "No students registered. Cannot create session.\n";
        return;
    }

    string courseCode;
    string date;

    cout << "Enter course code: ";
    cin >> courseCode;

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;

    string fileName = courseCode + "_" + date + "_attendance.txt";

    ofstream file;
    file.open(fileName.c_str());

    if (!file.is_open()) {
        cout << "Error creating file.\n";
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        file << students[i].indexNumber << ","
             << students[i].fullName << ",Absent" << endl;
    }

    file.close();

    cout << "Lecture session created successfully.\n";
}

// ================= MAIN =================
int main() {
    int choice;

    do {
        cout << "\nDIGITAL ATTENDANCE SYSTEM\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Create Lecture Session\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                createLectureSession();
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 0);

    return 0;
}


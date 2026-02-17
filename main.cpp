#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// ================= STUDENT CLASS =================
class Student {
public:
    string indexNo;
    string fullName;

    Student(string i, string n) {
        indexNo = i;
        fullName = n;
    }
};

// ================= GLOBAL STUDENT LIST =================
vector<Student> studentList;

// ================= WEEK 1 =================
void addStudent() {
    string index, name;
    cout << "Enter student index number: ";
    cin >> index;
    cin.ignore(); // ignore leftover newline

    cout << "Enter full name: ";
    getline(cin, name);

    studentList.push_back(Student(index, name));
    cout << "Student added successfully.\n";
}

void viewStudents() {
    if (studentList.empty()) {
        cout << "No students registered yet.\n";
        return;
    }

    cout << "\nRegistered Students:\n";
    for (int i = 0; i < studentList.size(); i++) {
        cout << studentList[i].indexNo << " - " << studentList[i].fullName << endl;
    }
}

// ================= WEEK 2 =================
string createSession() {
    string courseCode, date;
    cout << "Enter course code: ";
    cin >> courseCode;
    cout << "Enter lecture date (YYYY-MM-DD): ";
    cin >> date;

    string fileName = courseCode + "_" + date + "_attendance.txt";

    ofstream outFile(fileName.c_str());
    for (int i = 0; i < studentList.size(); i++) {
        outFile << studentList[i].indexNo << "," 
                << studentList[i].fullName << ",Absent" << endl;
    }
    outFile.close();

    cout << "\nLecture session created successfully!\n";
    cout << "Attendance file: " << fileName << endl;

    return fileName; // return filename for easy access
}

// ================= WEEK 3 =================
void markAttendance(const string &fileName) {
    ifstream inFile(fileName.c_str());
    if (!inFile) {
        cout << "File not found: " << fileName << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    string line, index, name, status;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        int comma1 = line.find(",");
        int comma2 = line.find(",", comma1 + 1);
        if (comma1 == -1 || comma2 == -1) continue;

        index = line.substr(0, comma1);
        name = line.substr(comma1 + 1, comma2 - comma1 - 1);
        status = line.substr(comma2 + 1);

        cout << "\nStudent: " << index << " - " << name << endl;
        cout << "Enter P for Present, L for Late, A for Absent: ";
        char ch;
        cin >> ch;

        if (ch == 'P' || ch == 'p') status = "Present";
        else if (ch == 'L' || ch == 'l') status = "Late";
        else status = "Absent";

        tempFile << index << "," << name << "," << status << endl;
    }

    inFile.close();
    tempFile.close();

    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());

    cout << "\nAttendance updated successfully.\n";
}

// ================= WEEK 4 =================
void viewReport(const string &fileName) {
    ifstream inFile(fileName.c_str());
    if (!inFile) {
        cout << "File not found: " << fileName << endl;
        return;
    }

    cout << "\nAttendance Report for " << fileName << "\n";
    cout << "--------------------------------------\n";

    string line, index, name, status;
    int total = 0, present = 0, absent = 0, late = 0;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        int comma1 = line.find(",");
        int comma2 = line.find(",", comma1 + 1);
        if (comma1 == -1 || comma2 == -1) continue;

        index = line.substr(0, comma1);
        name = line.substr(comma1 + 1, comma2 - comma1 - 1);
        status = line.substr(comma2 + 1);

        cout << index << " - " << name << " : " << status << endl;

        total++;
        if (status == "Present") present++;
        else if (status == "Absent") absent++;
        else if (status == "Late") late++;
    }

    inFile.close();

    cout << "--------------------------------------\n";
    cout << "Total Students: " << total << endl;
    cout << "Present: " << present << endl;
    cout << "Absent: " << absent << endl;
    cout << "Late: " << late << endl;
    if (total > 0) {
        cout << "Attendance Percentage: " << (present * 100) / total << "%\n";
    }
    cout << "--------------------------------------\n";
}

// ================= MAIN MENU =================
int main() {
    int option;
    string currentFile = ""; // store the current lecture file

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register student (Week 1)\n";
        cout << "2. View students (Week 1)\n";
        cout << "3. Create lecture session (Week 2)\n";
        cout << "4. Mark attendance (Week 3)\n";
        cout << "5. View attendance report (Week 4)\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> option;

        if (option == 1) addStudent();
        else if (option == 2) viewStudents();
        else if (option == 3) currentFile = createSession();
        else if (option == 4) {
            if (currentFile == "") {
                cout << "You need to create a lecture session first!\n";
            } else {
                markAttendance(currentFile);
            }
        }
        else if (option == 5) {
            if (currentFile == "") {
                cout << "You need to create a lecture session first!\n";
            } else {
                viewReport(currentFile);
            }
        }

    } while (option != 0);

    return 0;
}


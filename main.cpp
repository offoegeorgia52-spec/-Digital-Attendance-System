// ================= WEEK 4 =================
// View Attendance Report
void viewReport() {
    string fileName;
    cout << "Enter attendance file name: ";
    cin >> fileName;

    ifstream inFile(fileName.c_str());
    if (!inFile) {
        cout << "File not found.\n";
        return;
    }

    cout << "\nAttendance Report for " << fileName << "\n";
    cout << "--------------------------------------\n";

    string line, index, name, status;
    int total = 0, present = 0, absent = 0, late = 0;

    while (getline(inFile, line)) {
        if (line.empty()) continue; // skip blank lines

        int comma1 = line.find(",");
        int comma2 = line.find(",", comma1 + 1);

        if (comma1 == -1 || comma2 == -1) continue;

        index = line.substr(0, comma1);
        name = line.substr(comma1 + 1, comma2 - comma1 - 1);
        status = line.substr(comma2 + 1);

        cout << index << " - " << name << " : " << status << endl;

        // Count summary
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


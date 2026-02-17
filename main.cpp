// ================= WEEK 3 =================
void markAttendance() {
    string fileName;
    cout << "Enter attendance file name: ";
    cin >> fileName;

    ifstream inFile(fileName.c_str());

    if (!inFile) {
        cout << "File not found.\n";
        return;
    }

    string index, name, status;
    string tempFile = "temp.txt";

    ofstream outFile(tempFile.c_str());

    while (inFile >> index) {
        inFile.ignore(); // ignore comma
        getline(inFile, name, ',');
        getline(inFile, status);

        cout << index << "," << name << "," << status << endl;
        cout << "Mark (P=Present, L=Late, A=Absent): ";

        char choice;
        cin >> choice;

        if (choice == 'P' || choice == 'p')
            status = "Present";
        else if (choice == 'L' || choice == 'l')
            status = "Late";
        else
            status = "Absent";

        outFile << index << "," << name << "," << status << endl;
    }

    inFile.close();
    outFile.close();

    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());

    cout << "Attendance updated successfully.\n";
}


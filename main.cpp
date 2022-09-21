//
//  main.cpp
//  MonroeProject
//
//  Uliana Ozerova, John Meeks, 
//

#include <iostream>
#include "StudentList.h"

char getOption(); //gets and returns user action
bool addStudent(StudentList& sl); //function to add student
string getString(string field, int maxLen);
int getScore(string field);
bool delStudent(StudentList& sl); //function to delete student
bool searchStudent(StudentList& sl); //function to search for student
bool updateStudent(StudentList& sl); //function to update student info
bool printStudentList(StudentList sl); //function to print student list
bool printStudent(Student s);//print student
bool updateCSV(StudentList& sl);//rewrite CSV with updated list

std::string filePath = "Students.csv";

int main() {
    StudentList sl = StudentList(filePath);

    char option = ' ';
    std::cout << "			   	Welcome to the Student Databse" << std::endl;
    std::cout << "-------------------------------------------------------------------------------" << std::endl;

    while (option != 'q') {
        option = getOption();
        switch (option) {
        case 'a'://add student
            addStudent(sl);
            break;
        case 'd'://delete student
            delStudent(sl);
            break;
        case 's'://search/view student
            searchStudent(sl);
            break;
        case 'u'://update student
            updateStudent(sl);
            break;
        case 'v'://view all students
            printStudentList(sl);
            break;
        case 'q'://quit program
            return 0;
            break;
        }
    }

}

char getOption() {
    while (true) {
        std::cin.clear();
        string in;
        std::cout << std::endl << "What would you like to do?\na - 'add student'\nd - 'delete student'\ns - 'search/view student'\nv - 'view all records'\nu - 'update student info'\nq - 'quit program'\n\nOption: ";
        std::cin.clear();
        std::getline(std::cin, in);

        if (in.length() > 1) {
            std::cout << "\nERROR: Please only enter a single character\n";
            continue;
        }
        else if (in[0] == 'a' || in[0] == 'd' || in[0] == 's' || in[0] == 'u' || in[0] == 'q' || in[0] == 'v') {
            return in[0];
            break;
        }
        else {
            std::cout << "\nERROR: Please enter one of the listed characters\n";
            continue;
        }
    }
    return 'q';
}

bool addStudent(StudentList& sl) {
    string UID = getString("UID", 10);
    if (sl.IDexists(UID)) {
        std::cout << "UID already added\n";
        return 0;
    }

    string name = getString("name", 40);
    string email = getString("email", 40);

    int presGrade = getScore("presentation score");
    int essayGrade = getScore("essay score");
    int projGrade = getScore("project score");


    sl.addStudent(Student(name, UID, email, presGrade, essayGrade, projGrade));

    updateCSV(sl);

    return true;
}

bool searchStudent(StudentList& sl) {

    std::string search_term;
    bool isFound = false;
    Student tempst = Student();


        std::cout << "Please provide email, id, or name: " << std::endl;
        std::getline(std::cin, search_term);

        //use this tempst object to pass to another function if you need to return an object.

        for (Student s : sl.getStudents())
        {
            if (s.getEmail() == search_term || s.getName() == search_term || s.getId() == search_term) {
                isFound = true;
                tempst = s;
                break;
            }
        }

    if (isFound) {
        std::cout << "Found!" << std::endl;
        printStudent(tempst);
        return true;
    }
    else {
        std::cout << "User not found" << std::endl;
        return false;
    }

}


string getString(string field, int maxLen) {
    while (true) {
        std::cin.clear();
        string in;
        std::cout << "\nPlease enter the " << field << " of the student you are adding: ";
        std::getline(std::cin, in);
        if (in.length() > maxLen || in.length() < 1) {
            std::cout << "\nERROR: " << field << " must not exceed " << maxLen << " characters in length, or be empty.\n";
            continue;
        }
        else {
            return in;
            break;
        }
    }
    return "";
}

int getScore(string field) {
    while (true) {
        std::cin.clear();
        int in;
        std::cout << "\nPlease enter the " << field << " of the student you are adding(999 if no grade): ";
        while (!(std::cin >> in)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nERROR: " << field << " must be a number.\nPlease enter the " << field << " of the student you are adding: ";
        }

        if ((in > 4 && in != 999) || in < 0) {
            std::cout << "\nERROR: " << field << " must be between 0 and 4.\n";
            continue;
        }
        else {
            return in;
            break;
        }
    }
}

bool delStudent(StudentList& sl) {
    std::cin.clear();
    string uid;
    std::cout << "\nPlease enter the UID of the student you would like to delete: ";
    std::getline(std::cin, uid);

    if (!(sl.deleteStudent(uid))) {
        std::cout << "\nError deleting " << uid << "\n";
    }
    else {
        std::cout << "\Successfully deleted " << uid << "\n";
    }

    updateCSV(sl);

    return true;
}

bool updateStudent(StudentList& sl) {

    return true;
}

bool printStudentList(StudentList sl) {
    std::cout << std::left << std::setw(20) << "Name"
        << std::left << std::setw(20) << "USF ID"
        << std::left << std::setw(20) << "Email"
        << std::left << std::setw(20) << "Grade1"
        << std::left << std::setw(20) << "Grade2"
        << std::left << std::setw(20) << "Grade3" << std::endl;

    for (Student s : sl.getStudents())
    {
        printStudent(s);
    }

    return true;
}

bool printStudent(Student s) {
    std::cout << std::left << std::setw(20) << s.getName();
    std::cout << std::left << std::setw(20) << s.getId();
    std::cout << std::left << std::setw(20) << s.getEmail();
    std::cout << std::left << std::setw(20) << s.getPresentationGrade();
    std::cout << std::left << std::setw(20) << s.getEssayGrade();
    std::cout << std::left << std::setw(20) << s.getProjectGrade() << std::endl;

    return true;
}

bool updateCSV(StudentList& sl) {
    //rewrite entire CSV with any updates
    if (sl.writeListToCSV(filePath)) {
        //successfully written
        return true;
    }
    //error writing
    return false;
}

//
//  main.cpp
//  MonroeProject
//
//  Team Monroe: Uliana Ozerova, John Meeks, Maanasa Poluparti, Ayden Malik
//  hello

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <limits>
//#include "StudentList.h"
using std::string;

class Student {
private:
    string name;
    string id;
    string email;
    int presentation_grade;
    int essay_grade;
    int project_grade;

public:
    void setName(string Name) {
        name = Name;
    }
    string getName() {
        return name;
    }
    void setId(string Id) {
        id = Id;
    }
    string getId() {
        return id;
    }
    void setEmail(string Email) {
        email = Email;
    }
    string getEmail() {
        return email;
    }

    void setPresentationGrade(int grade) {
        presentation_grade = grade;
    }

    int getPresentationGrade() {
        return presentation_grade;
    }
    void setEssayGrade(int grade) {
        essay_grade = grade;
    }

    int getEssayGrade() {
        return essay_grade;
    }
    void setProjectGrade(int grade) {
        project_grade = grade;
    }

    int getProjectGrade() {
        return project_grade;
    }

    Student(string Name, string Id, string Email) {
        name = Name;
        id = Id;
        email = Email;
        /*presentation_grade = -999;
        essay_grade = -999;
        project_grade = -999;*/
    }

    Student(string Name, string Id, string Email, int presG, int essayG, int projG) {
        name = Name;
        id = Id;
        email = Email;
        presentation_grade = presG;
        essay_grade = essayG;
        project_grade = projG;
    }

    Student() {}

    Student(string studentInfo) {
        std::istringstream studentStream(studentInfo);

        std::string token;

        std::vector <std::string> v;

        while (std::getline(studentStream, token, ',')) {
            v.push_back(token);
        }

        name = v[0];
        id = v[1];
        email = v[2];
        presentation_grade = std::stoi(v[3]);
        essay_grade = std::stoi(v[4]);
        project_grade = std::stoi(v[5]);

        v.clear();
    }
};



class StudentList {

private:
    std::vector <Student> students;
public:
    StudentList(std::string filePath) {
        std::ifstream studentFile(filePath);

        std::string lineContents;
        if (studentFile.is_open()) {
            while (getline(studentFile, lineContents)) {
                if (lineContents.length() == 0) continue;
                Student st = Student(lineContents);
                students.push_back(st);

            }
        }
    }

    std::vector <Student> getStudents() {
        return students;
    }

    void addStudent(Student st) {
        students.push_back(st);
    }

    bool deleteStudent(string uid) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == uid) {
                students.erase(students.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool IDexists(string uid) {

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == uid) return true;
        }
        return false;
    }

    bool writeListToCSV(string filePath) {
        std::ofstream appendCSV;
        appendCSV.open(filePath, std::ios_base::trunc);
        for (int i = 0; i < students.size(); i++) {
            string CSVFormat = students[i].getName() + "," + students[i].getId() + "," + students[i].getEmail() + "," + std::to_string(students[i].getPresentationGrade()) + "," + std::to_string(students[i].getEssayGrade()) + "," + std::to_string(students[i].getProjectGrade()) + "\n";
            appendCSV << CSVFormat;
        }

        appendCSV.close();
        return true;
    }

    void overrideVector(std::vector <Student> replacement) {
        students = replacement;
    }
};

char getOption(); //gets and returns user action
char getUpdateOption(); //gets and returns user action for UpdateStudent()
bool addStudent(StudentList& sl); //function to add student
string getString(string field, int maxLen);
int getScore(string field);
bool delStudent(StudentList& sl); //function to delete student
bool searchStudent(StudentList& sl); //function to search for student
bool updateStudent(StudentList& sl); //function to update student info
bool printStudentList(StudentList sl); //function to print student list
bool printStudent(Student s);//print student
bool updateCSV(StudentList& sl);//rewrite CSV with updated list
bool checkID(std::string uid);
std::string makeUpperCase(std::string str);
bool checkEmail(std::string email);
std::string makeLowerCase(std::string str);
std::string trimString(std::string str);
bool hasSpecialCharactersOrNumbers(std::string str);

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

std::string trimString(std::string str) {
    size_t first = str.find_first_not_of(' ');

    //if string is empty
    if (string::npos == first) {
        //return the original string
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    std::string str_new = str.substr(first, (last - first + 1));

    return str_new;
}

bool checkEmail(std::string email) {

    std::string email_postfix = "@usf.edu";

    if (email.length() >= email_postfix.length())
        if (email.compare(email.length() - email_postfix.length(), email_postfix.length(), email_postfix) == 0)
            return true;
        else
            return false;
    else
        return false;

}

bool hasSpecialCharactersOrNumbers(std::string str) {

    bool hasChars = false;
    std::size_t found = str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz `'");

    if (found != std::string::npos) {
        hasChars = true;
    }

    return hasChars;
}


char getOption() {
    while (true) {
        string in;
        std::cout << std::endl << "What would you like to do?\na - 'add student'\nd - 'delete student'\ns - 'search/view student'\nv - 'view all records'\nu - 'update student info'\nq - 'quit program'\n\nOption: ";
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

char getUpdateOption() {
    while (true) {
        string in;
        std::cout << std::endl
            << "What would you like to update?\nn - 'name'\nm - 'email'\np - 'presentation score'\ne - 'essay score'\nr - 'project score'\nq = 'go back to the menu'\n\nOption: ";
        std::getline(std::cin, in);

        if (in.length() > 1) {
            std::cout << "\nERROR: Please only enter a single character\n";
            continue;
        }
        else if (in[0] == 'n' || in[0] == 'm' || in[0] == 'p' || in[0] == 'e' || in[0] == 'r' || in[0] == 'q') {
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

bool checkID(std::string uid) {
    std::string prefix = "U";

    bool isGood = true;

    //If UID starts with U, check that the rest is numeric
    if (uid.length() == 9) {
        if ((uid.rfind("U", 0) == 0) || (uid.rfind("u", 0) == 0)) {

            //go through the string, checking that the rest are digits
            for (int i = 1; i < uid.length(); i++) {
                if (isdigit(uid[i]) == false) {
                    isGood = false;
                    break;
                }
                else
                    isGood = true;
            }
        }
        else
            isGood = false;
    }
    else {
        isGood = false;
        std::cout << "Not enough characters" << std::endl;
    }

    return isGood;
}

std::string makeUpperCase(std::string str) {

    std::string str_new;
    char ch;
    for (int i = 0; i < str.length(); i++) {
        ch = toupper(str[i]);
        str_new = str_new + ch;
    }

    return str_new;
}

std::string makeLowerCase(std::string str) {

    std::string str_new = "";
    char ch;
    for (int i = 0; i < str.length(); i++) {
        ch = tolower(str[i]);
        str_new = str_new + ch;
    }

    return str_new;
}
bool addStudent(StudentList& sl) {

    /*USF ID*/

    string UID;

    //if ID is not properlt formatted, ask to reenter the ID
    while (true) {
        UID = getString("UID", 9);
        UID = trimString(UID);
        UID = makeUpperCase(UID);
        bool bool_id = checkID(UID);

        if (bool_id == false) {
            std::cout << "The ID is not valid." << std::endl;
            continue;
        }
        else
            break;
    }

    if (sl.IDexists(UID)) {
        std::cout << "UID already added\n";
        return 0;
    }

    /* NAME */

    string name = "";

    while (true) {
        name = getString("name", 40);
        name = trimString(name);

        if (hasSpecialCharactersOrNumbers(name)) {
            std::cout << "The name contains special characters or numbers." << std::endl;
            continue;
        }
        else
            break;
    }

    /* EMAIL */
    string email;
    while (true) {
        email = getString("email", 40);
        email = trimString(email);
        email = makeLowerCase(email);
        bool bool_email = checkEmail(email);

        if (bool_email == false) {
            std::cout << "The email is not valid." << std::endl;
            continue;
        }
        else
            break;
    }

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
    search_term = trimString(search_term);

    //use this tempst object to pass to another function if you need to return an object.

    for (Student s : sl.getStudents())
    {
        if (s.getEmail() == makeLowerCase(search_term) || s.getName() == search_term || s.getId() == makeUpperCase(search_term)) {
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
        std::cout << "User not found!" << std::endl;
        return false;
    }

}


string getString(string field, int maxLen) {
    while (true) {
        std::cin.clear();
        string in;
        std::cout << "\nPlease enter the " << field << " of the student: ";
        std::getline(std::cin, in);
        if (in.length() > maxLen || in.length() < 1 || in.find(',') != std::string::npos) {
            std::cout << "\nERROR: " << field << " must not exceed " << maxLen << " characters in length, be empty, or contain commas.\n";
            continue;
        }
        else {
            return in;
        }
    }
}

int getScore(string field) {
    while (true) {
        int in;
        std::cout << "\nPlease enter the " << field << " of the student(999 if no grade): ";
        while (!(std::cin >> in)) {
            std::cout << "\nERROR: " << field << " must be a number.\nPlease enter the " << field << " of the student you are adding: ";
        }

        if ((in > 4 && in != 999) || in < 0) {
            std::cout << "\nERROR: " << field << " must be between 0 and 4.\n";
            continue;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return in;
        }
    }
}

bool delStudent(StudentList& sl) {
    string uid;
    std::cout << "\nPlease enter the UID of the student you would like to delete: ";
    std::getline(std::cin, uid);

    if (!(sl.deleteStudent(uid))) {
        std::cout << "\nError deleting " << uid << "\n";
    }
    else {
        std::cout << "\nSuccessfully deleted " << uid << "\n";
    }

    updateCSV(sl);

    return true;
}

bool updateStudent(StudentList& sl) {
    string UID;

    // if ID is not properlt formatted, ask to reenter the ID
    while (true) {
        UID = getString("UID", 10);
        UID = trimString(UID);
        UID = makeUpperCase(UID);
        bool bool_id = checkID(UID);

        if (bool_id == false) {
            std::cout << "The ID is not valid." << std::endl;
            continue;
        }
        else
            break;
    }

    if (!(sl.IDexists(UID))) {
        std::cout << "\nUID does not exist\n";
        return 0;
    }

    char option = ' ';

    std::cin.clear();

    while (option != 'q') {
        option = getUpdateOption();
        std::vector <Student> tempvector = sl.getStudents();

        for (Student& s : tempvector) {
            if (s.getId() == UID) {

                std::cout << std::left << std::setw(20) << "Name"
                    << std::left << std::setw(20) << "USF ID"
                    << std::left << std::setw(20) << "Email"
                    << std::left << std::setw(20) << "Presentation"
                    << std::left << std::setw(20) << "Essay"
                    << std::left << std::setw(20) << "Project" << std::endl;
                printStudent(s);
                switch (option) {
                case 'n': // update name

                    while (true) {
                        string name = getString("name", 40);
                        name = trimString(name);

                        if (hasSpecialCharactersOrNumbers(name)) {
                            std::cout << "The name contains special characters or numbers." << std::endl;
                            continue;
                        }
                        else {
                            s.setName(name);
                        }
                        break;
                    }

                    break;

                case 'm': // update email

                    while (true) {
                        string email = getString("email", 40);
                        email = trimString(email);
                        email = makeLowerCase(email);
                        bool bool_email = checkEmail(email);

                        if (bool_email == false) {
                            std::cout << "The email is not valid." << std::endl;
                            continue;
                        }
                        else {
                            s.setEmail(email);
                        }
                        break;
                    }

                    break;
                case 'p': // update presentation score
                {
                    int presGrade = getScore("presentation score");
                    s.setPresentationGrade(presGrade);
                    break;
                }
                case 'e': // update essay score
                {
                    int essayGrade = getScore("essay score");
                    s.setEssayGrade(essayGrade);
                    printStudent(s);
                    break;
                }
                case 'r': // update project score
                {
                    int projGrade = getScore("project score");
                    s.setProjectGrade(projGrade);
                    break;
                }
                case 'q': // quit program
                    return 0;
                    break;
                }
                sl.overrideVector(tempvector);
                updateCSV(sl);
                break;
            }
        }
    }
    return true;
}

bool printStudentList(StudentList sl) {
    std::cout << std::left << std::setw(20) << "Name"
        << std::left << std::setw(20) << "USF ID"
        << std::left << std::setw(20) << "Email"
        << std::left << std::setw(20) << "Presentation"
        << std::left << std::setw(20) << "Essay"
        << std::left << std::setw(20) << "Project" << std::endl;

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

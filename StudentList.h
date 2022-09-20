#include "Student.hpp"

class StudentList {
public:
    StudentList(std::string filePath) {
        std::ifstream studentFile(filePath);

        std::string lineContents;
        if (studentFile.is_open()) {
            while (getline(studentFile, lineContents)) {
                if (lineContents.length() == 0)continue;
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

private:
    std::vector <Student> students;
};

#include "Student.hpp"

class StudentList {
public:

	StudentList(std::string filePath) {
		std::ifstream studentFile(filePath);

		std::string lineContents;

		while (!studentFile.eof()) {
			getline(studentFile, lineContents);

			Student st = Student(lineContents);
			students.push_back(st);
		}
	}

	std::vector <Student> getStudents() {
		return students;
	}
private:
	std::vector <Student> students;
};
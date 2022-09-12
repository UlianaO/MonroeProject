#include <iostream>
#include <fstream>
#include <string>

#include "StudentList.h"

void printStudent(Student s) {
	std::cout << "Name: " << s.getName() << std::endl;
	std::cout << "ID: " << s.getId() << std::endl;
	std::cout << "Email: " << s.getEmail() << std::endl;
	std::cout << "G1: " << s.getPresentationGrade() << std::endl;
	std::cout << "G2: " << s.getEssayGrade() << std::endl;
	std::cout << "G3: " << s.getProjectGrade() << std::endl;
}

int main() {

	std::string filePath = "Students.csv";

	StudentList sl = StudentList(filePath);

	for (Student s : sl.getStudents())
	{
		printStudent(s);
	}


	return 0;
}

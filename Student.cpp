#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "StudentList.h"

using namespace std;


void printStudent(Student s) {

	std::cout << left << setw(20) << s.getName();
	std::cout << left << setw(20) << s.getId();
	std::cout << left << setw(20) << s.getEmail();
	std::cout << left << setw(20) << s.getPresentationGrade();
	std::cout << left << setw(20) << s.getEssayGrade();
	std::cout << left << setw(20) << s.getProjectGrade() << endl;
}

using namespace std;

void showAllRecords(StudentList sl) {

	cout << left << setw(20) << "Name"
		<< left << setw(20) << "USF ID"
		<< left << setw(20) << "Email"
		<< left << setw(20) << "Grade1"
		<< left << setw(20) << "Grade2"
		<< left << setw(20) << "Grade3" << endl;

	for (Student s : sl.getStudents())
	{
		printStudent(s);
	}

}

int main() {

	std::string filePath = "Students.csv";

	StudentList sl = StudentList(filePath);
	
	//show all students
	showAllRecords(sl);

	char user_choice;

	// if append is chosen, we are asking to provide the information - that is, we have to create the student - Student(string student info)

	std::fstream studentFile;
	studentFile.open(filePath, std::ios::app);

	// MAIN MENU HERE



	std::cout << "Click a to append the student: " << std::endl;
	std::cin >> user_choice;
	do {
		if (user_choice != 'A') {
			std::cout << "Wrong character, try again.(a)" << std::endl;
			std::cin >> user_choice;
		}
	} while (user_choice != 'a');

		//std::cout << "Wrong input, choose a" << std::endl;

	/*if (studentFile.is_open()) {
		studentFile << std::endl << "Test File" << ", " << "testing" << ", " << "testmail" << ", " << 3 << ", " << 4 << ", " << 5;
		studentFile.close();
	} */


	return 0;
}

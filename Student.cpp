#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctype.h>

#include "StudentList.h"

using namespace std;

// TEST COMMIT 1

void printStudent(Student s) {

	std::cout << left << setw(20) << s.getName();
	std::cout << left << setw(20) << s.getId();
	std::cout << left << setw(20) << s.getEmail();
	std::cout << left << setw(20) << s.getPresentationGrade();
	std::cout << left << setw(20) << s.getEssayGrade();
	std::cout << left << setw(20) << s.getProjectGrade() << endl;
}

bool searchStudent(StudentList& sl, std::string search_term) {

	bool isFound = false;

	Student tempst = Student();

	for (Student s : sl.getStudents())
	{
		if (s.getEmail() == search_term || s.getName() == search_term || s.getId() == search_term) {
			isFound = true;
			tempst = s;
		}
	}

	if (isFound)
		return true;
	else
		return false;

	printStudent(tempst);

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

	// MAIN MENU HERE
	std::cout << "			   	Welcome to the Student Databse" << std::endl;
	std::cout << "-------------------------------------------------------------------------------" << std::endl;

	std::string filePath = "Students.csv";

	StudentList sl = StudentList(filePath);

	
	//show all students
	showAllRecords(sl);

	char user_choice;
	std::string search_term;
	bool isFound;

	std::cout << "Click s to search the student: " << std::endl;
	std::cin >> user_choice;
	do {
		if (tolower(user_choice) != 's') {
			std::cout << "Wrong character, try again.(s)" << std::endl;
			std::cin >> user_choice;
		}
		else {
			std::cout << "Please provide email, id, or name: " << std::endl;
			std::cin >> search_term;
			isFound = searchStudent(sl, search_term);

			if (isFound)
				std::cout << "User found" << std::endl;
			else
				std::cout << "User not found" << std::endl;
		}

	} while (tolower(user_choice) != 's');






		//std::cout << "Wrong input, choose a" << std::endl;

	/*if (studentFile.is_open()) {
		studentFile << std::endl << "Test File" << ", " << "testing" << ", " << "testmail" << ", " << 3 << ", " << 4 << ", " << 5;
		studentFile.close();
	} */


	return 0;
}

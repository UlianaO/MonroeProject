
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>
#include <sstream>
#include <iostream>

using std::string;

class Student {
private:
	string name;
	string id;
	string email;
	int presentation_grade;
	int essay_grade;
	int project_grade;

	string firstName;
	string lastName;


public:
	void setName(string Name) {
		Name = name;
	}
	string getName() {
		return name;
	}
	void setId(string Id) {
		Id = id;
	}
	string getId() {
		return id;
	}
	void setEmail(string Email) {
		Email = email;
	}
	string getEmail() {
		return email;
	}

	void setFirstName(string Name) {
		firstName = Name;
	}
	string getFirstName() {
		return firstName;
	}

	void setLastName(string Name) {
		firstName = Name;
	}
	string getLirstName() {
		return lastName;
	}

	void setPresentationGrade(string grade) {
		presentation_grade = stoi(grade);
	}

	int getPresentationGrade() {
		return presentation_grade;
	}
	void setEssayGrade(string grade) {
		essay_grade = stoi(grade);
	}

	int getEssayGrade() {
		return essay_grade;
	}
	void setProjectGrade(string grade) {
		project_grade = stoi(grade);
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

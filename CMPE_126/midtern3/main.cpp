#include <iostream>
#include <fstream>
#include "Student.cpp"
using namespace std;

#define MAXSTUDENTS 64

int myHash(int id) {
	//base case that id is nothing
	if(id <= 0) {
		return 0;
	}

	//last two digits
	int index = id%100;

	//rehashing the next two digits instead
	if(index >= 64) {
		myHash((id - id%100)/100);
	}
	else {
		return index;
	}
}

void addStudent(Student student, Student* students) {
	int index = myHash(stoi(student.getId()));

	for(int i=index; i<index+10;i++) { //the function only probes 10 indexes
		if(students[i].getId().empty()) {
			students[i] = student;
			return;
		}
	}
	return;
}

int read(string filename, Student* students){
	ifstream fin(filename);
	int index = 0;
	while(!fin.eof() && index < MAXSTUDENTS){
		Student temp;
		string word;
		getline(fin, word, ',');
		temp.setId(word);
		getline(fin, word, ',');
		temp.setFirstName(word);
		getline(fin, word);
		temp.setLastName(word);
		addStudent(temp, students); //hashes student into array rather than on index
		index++;
	}
	return index;
}

int search(Student* students, Student student, int num_students) {

	int index = myHash(stoi(student.getId()));

	for(int i=index; i<index+10;i++) { //the function only probes 10 indexes
		if((students+i)->getId() == student.getId()) {
			return i;
		}
	}
	return -1; //not found
}

void addStudents(string fileName, Student* students) {
	int num_students2 = read(fileName, students); //already hashes students in constant time into the array
	cout << "done" << endl;
}


// Uncomment above line to implement the A-level task.


int main() {
	Student *students = new Student[MAXSTUDENTS];
	int num_students = read("students.txt", students);
	/*******************************************************
	 * TODO: Implement your code here:
	 * 1. Take user input - student ID is sufficient
	 * 2. Search for the student using your choice of search algorithm
	 * 3. Take user input to add student to the list
	 * 4. Add the student using addStudent
	 ******************************************************/
	Student temp;
	string tempID = "";

	cout << "Please enter the id of the student you want to search: " << endl;
	cin >> tempID;
	temp.setId((tempID));
	int result = search(students, temp, num_students);
	cout << "The index of that student is: " << result << endl;

	cout << "Please enter the id of the student you want to add: " << endl;
	cin >> tempID;
	temp.setId((tempID));
	addStudent(temp, students);
	cout << "Student is successfully been added!" << endl;

	string fileName = "";
	cout << "Please enter the file name with students you want to add (ie newstudents.txt)" << endl;
	cin >> fileName;
	addStudents(fileName, students);

	delete [] students;
	return 0;
}

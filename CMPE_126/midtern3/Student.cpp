/*
 * Student.cpp
 *
 *      Author: Mahima
 */

#include "Student.h"

Student::Student() {
	ID = "";
	firstName = "";
	lastName = "";
}

const string& Student::getFirstName() const {
	return firstName;
}

void Student::setFirstName(const string& firstName) {
	this->firstName = firstName;
}

string Student::getId() const {
	return ID;
}

void Student::setId(string id) {
	ID = id;
}

const string& Student::getLastName() const {
	return lastName;
}

void Student::setLastName(const string& lastName) {
	this->lastName = lastName;
}

Student::~Student() {
	// TODO Auto-generated destructor stub
}


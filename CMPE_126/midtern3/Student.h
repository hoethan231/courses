/*
 * Student.h
 *
 *      Author: Mahima
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
using namespace std;

class Student {
private:
	string ID;
	string firstName;
	string lastName;

public:
	Student();
	virtual ~Student();
	const string& getFirstName() const;
	void setFirstName(const string& firstName);
	string getId() const;
	void setId(string id);
	const string& getLastName() const;
	void setLastName(const string& lastName);
};

#endif /* STUDENT_H_ */

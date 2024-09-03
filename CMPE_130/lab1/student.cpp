#include "student.h"

Student::Student() {
    this->id = 0;
    this->first = "john";
    this->last = "doe";
    this->grade = "freshman";
}

Student::Student(int id, std::string first, std::string last, std::string grade) {
    this->id = id;
    this->first = first;
    this->last = last;
    this->grade = grade;
}

void Student::setID(int id) {
    this->id = id;
}

void Student::setFirst(std::string first) {
    this->first = first;
}

void Student::setLast(std::string last) {
    this->last = last;
}

void Student::setGrade(std::string grade) {
    this->grade = grade;
}

int Student::getID() {
    return this->id;
}

std::string Student::getFirst() {
    return this->first;
}

std::string Student::getLast() {
    return this->last;
}

std::string Student::getGrade() {
    return this->grade;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << student.first << " " << student.last;
    return os;
}
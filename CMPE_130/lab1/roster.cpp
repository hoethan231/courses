#include <iostream>
#include "roster.h"
#include "student.h"

Roster::Roster() {
    this->capacity = 30;
    this->size = 0;
    this->array = new Student[capacity];
}

Roster::Roster(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->array = new Student[capacity];
}

Roster::~Roster() {
    delete[] array;
}

void Roster::expand() {
    this->capacity *= 2;
    Student* newArr = new Student[this->capacity];
    for(int i=0; i<size; i++) {
        newArr[i] = this->array[i];
    }
    delete[] this->array;
    this->array = newArr;
}

bool Roster::isEmpty() {
    return this->size == 0;
}

bool Roster::isFull() {
    return this->capacity == this->size;
}

int Roster::getCapacity() {
    return this->capacity;
}

int Roster::getSize() {
    return this->size;
}

void Roster::insert(Student student) {

    if (isFull()) { expand(); }

    int i = this->size;
    int newStudentAscii = (int)(student.getFirst()[0,1]);
    int currStudentAscii = (int)(this->array[i-1].getFirst()[0,1]);

    while( currStudentAscii >= newStudentAscii ) {
        this->array[i] = this->array[i-1];
        i--;
    }
    this->array[i] = student;
    this->size++;

}

void Roster::remove(Student student) {

    if( isEmpty() ) { 
        std::cout << "The roster is empty" << std::endl;
        return;
    }

    int i = this->size-1;
    int currID = this->array[i].getID();

    while( currID != student.getID() ) {
        this->array[i] = this->array[i+1];
    }
    this->size--;

}

void Roster::update(Student student, int id, std::string first, std::string last, std::string grade) {

    if( isEmpty() ) { 
        std::cout << "The roster is empty" << std::endl;
        return;
    }

    int updateStudentAscii = (int)(student.getFirst()[0,1]);
    int left = 0;
    int right = this->size;

    while( left <= right ) {
        int mid = left + ( right - left ) / 2;
        int currStudentAscii = (int)(this->array[mid].getFirst()[0,1]);

        if (currStudentAscii > updateStudentAscii) {
            right = mid - 1;
        }
        else if (currStudentAscii < updateStudentAscii) {
            left = mid + 1;
        }
        else {
            this->array[mid].setID(id);
            this->array[mid].setFirst(first);
            this->array[mid].setLast(last);
            this->array[mid].setGrade(grade);
            break;
        }
    }

    std::cout << "Student not found" << std::endl;

}

void Roster::printAll() {

    for(int i = 0; i < this->size; i++) {
        std::cout << this->array[i] << ", ";
    }

}

void Roster::clear() {
    if (array != nullptr) {
        delete[] this->array;
    }
    this->size = 0;
    this->array = new Student[this->capacity];
}



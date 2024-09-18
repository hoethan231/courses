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

    while( i > 0 && currStudentAscii >= newStudentAscii ) {
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
            return;
        }
    }

    std::cout << "Student not found" << std::endl;

}

void Roster::printAll() {

    if( isEmpty() ) { 
        std::cout << "The roster is empty" << std::endl;
        return;
    }

    for(int i = 0; i < this->size; i++) {
        std::cout << this->array[i] << ", ";
    }
    std::cout << std::endl;

}

void Roster::clear() {

    if (array != nullptr) {
        delete[] this->array;
    }
    this->size = 0;
    this->array = new Student[this->capacity];

}

void Roster::insertionSort() {

    for(int i=1; i<(this->size)-1; i++) {
        int j = i;
        int currASCII = (int)(this->array[j].getFirst()[0,1]);
        int prevASCII = (int)(this->array[j-1].getFirst()[0,1]);
        while(j>0 && currASCII < prevASCII) {
            Student temp = this->array[j];
            this->array[j] = this->array[j-1];
            this->array[j-1] = temp;
            j--;
        }
    }

}

void Roster::selectionSort() {
    
    for(int i=0; i<this->size-1; i++) {
        int minASCII = (int)(this->array[i].getFirst()[0,1]);
        int minASCIIIndex = i;
        int currASCII = minASCII;

        for(int j=i+1; j<this->size; j++) {
            if(currASCII < minASCII) {
                minASCII = currASCII;
                minASCIIIndex = i;
            }
        }

        Student temp = this->array[i];
        this->array[i] = this->array[minASCIIIndex];
        this->array[minASCIIIndex] = temp;
    }

}

int Roster::partition(int left, int right) {

    int pivot = (int)(this->array[right].getFirst()[0,1]);
    int i = left - 1;

    for (int j=left; j <= right-1; j++) {
        int curr = (int)(this->array[j].getFirst()[0,1]);
        if ( curr < pivot ) {
            i++;
            Student temp = this->array[i];
            this->array[i] = this->array[j];
            this->array[j] = temp;
        }
    }

    Student temp = this->array[i+1];
    this->array[i+1] = this->array[right];
    this->array[right] = temp;
    return i + 1;

}

void Roster::quickSort(int left, int right) {

    if (left < right) {
        int parIdx = partition(left, right);
        quickSort(left, parIdx - 1);
        quickSort(parIdx + 1, left);
    }

}

void Roster::heapify(int size, int i) {

    int largest = i;
    int leftChild = 2*i + 1;
    int rightChild = 2*i + 2;

    //heap sort by grade
    if(leftChild < size && this->array[leftChild].getGrade() > this->array[i].getGrade()) {
        largest = leftChild;
    }

    if(rightChild < size && this->array[rightChild].getGrade() > this->array[i].getGrade()) {
        largest = rightChild;
    }

    if(largest != i) {
        Student temp = this->array[i];
        this->array[i] = this->array[largest];
        this->array[largest] = temp;
        heapify(size, largest);
    }
}

void Roster::heapSort(int size) {

    for(int i=size/2 - 1; i >=0; i--) {
        heapify(size, i);
    }

    for(int i=size-1; i > 0; i--) {
        Student temp = this->array[0];
        this->array[0] = this->array[i];
        this->array[i] = temp;
        heapify(i, 0);
    }
}
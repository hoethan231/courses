#include "arrayList.hpp"

ArrayList::ArrayList() {
    this->size = 10;
    this->numOfElements = 0;
    this->array = new int[size];
}

ArrayList::ArrayList(int size) {
    this->size = size;
    this->numOfElements = 0;
    this->array = new int[size];
}

ArrayList::~ArrayList() {
    delete[] array;
}

bool ArrayList::isEmpty() const {
    return numOfElements == 0;
}

bool ArrayList::isFull() const {
    return numOfElements == size;
}

int ArrayList::listSize() const {
    return this->numOfElements;
}

int ArrayList::maxListSize() const {
    return this->size;
}

void ArrayList::print() {
    for(int i=0; i<size;i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

void ArrayList::expand() {
    int* newArray = new int[size*2];
    for(int i=0; i<size; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    size *= 2;
    array = newArray;
}

bool ArrayList::isItemAtEqual(int i, int num) {
    if(i < 0 || i > size-1) {
        cout << "index is out of bounds" << endl;
    }
    else { 
        return array[i] == num; 
    }
}

void ArrayList::insertAt(int i, int num) {
    if(i < 0 || i > size-1) {
        cout << "index is out of bounds" << endl;
    }
    else { 
        if(isFull()) { expand(); }
        for(int j=numOfElements; j>i; j--) {
            array[j] = array[j-1];
        }
        array[i] = num;
        numOfElements++;
    }   
}

void ArrayList::insertEnd(int num) {
    if(isFull()) { expand(); }
    array[size-1] = num;
    numOfElements++;
}

void ArrayList::removeAt(int i) {
    if(i < 0 || i > numOfElements) {
        cout << "index is out of bounds" << endl;
        return;
    }
    else { 
        for(int j=i; j<numOfElements-1; j++) {
            array[i] = array[i+1];
        }
        numOfElements--;
    } 
}

int ArrayList::retreiveAt(int i) {
    if(i < 0 || i > size-1) {
        cout << "index is out of bounds" << endl;
        return 0;
    }
    else { 
        return array[i];
    } 
}

void ArrayList::replaceAt(int i, int num) {
    if(i < 0 || i > size-1) {
        cout << "index is out of bounds" << endl;
    }
    else { 
        array[i] = num;
    } 
}

void ArrayList::clearList() {
    numOfElements = 0;
}

ArrayList& ArrayList::operator=(ArrayList& arr) {

    delete[] this->array;

    size = arr.maxListSize();
    numOfElements = arr.listSize();

    array = new int[size];
    for(int i=0; i<arr.listSize(); i++) {
        array[i] = arr.retreiveAt(i);
    }

    return *this;

}
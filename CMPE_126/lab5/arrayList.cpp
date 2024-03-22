
#include "arrayList.hpp"

template<typename e>

ArrayList<e>::ArrayList() {
    this->size = 10;
    this->numOfElements = 0;
    this->array = new e[size];
}

template<typename e>
ArrayList<e>::ArrayList(int size) {
    this->size = size;
    this->numOfElements = 0;
    this->array = new e[size];
}

template<typename e>
ArrayList<e>::~ArrayList() {
    delete[] array;
}

template<typename e>
bool ArrayList<e>::isEmpty() const {
    return numOfElements == 0;
}

template<typename e>
bool ArrayList<e>::isFull() const {
    return numOfElements == size;
}

template<typename e>
int ArrayList<e>::listSize() const {
    return this->numOfElements;
}

template<typename e>
int ArrayList<e>::maxListSize() const {
    return this->size;
}

template<typename e>
void ArrayList<e>::print() {

    cout << "[";
    for(int i=0; i<numOfElements;i++) {
        cout << array[i];
        if(!(i==numOfElements-1)) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

template<typename e>
void ArrayList<e>::expand() {
    e* newArray = new int[size*2];
    for(int i=0; i<numOfElements; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    size *= 2;
    array = newArray;
}

template<typename e>
bool ArrayList<e>::isItemAtEqual(int i, e num) {
    if(i < 0 || i > numOfElements-1) {
        cout << "index is out of bounds" << endl;
        return false;
    }
    else { 
        return array[i] == num; 
    }
}

template<typename e>
void ArrayList<e>::insertAt(int i, e num) {
    if(i < 0 || i > numOfElements-1) {
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

template<typename e>
void ArrayList<e>::insertEnd(e num) {
    if(isFull()) { expand(); }
    array[numOfElements] = num;
    numOfElements++;
}

template<typename e>
void ArrayList<e>::removeAt(int i) {
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

template<typename e>
e ArrayList<e>::retreiveAt(int i) {
    if(i < 0 || i > numOfElements-1) {
        cout << "index is out of bounds" << endl;
        return 0;
    }
    else { 
        return array[i];
    } 
}

template<typename e>
void ArrayList<e>::replaceAt(int i, e num) {
    if(i < 0 || i > numOfElements-1) {
        cout << "index is out of bounds" << endl;
    }
    else { 
        array[i] = num;
    } 
}

template<typename e>
void ArrayList<e>::clearList() {
    numOfElements = 0;
}

template<typename e>
ArrayList<e>& ArrayList<e>::operator=(ArrayList<e>& arr) {

    delete[] this->array;

    size = arr.maxListSize();
    numOfElements = arr.listSize();

    array = new int[size];
    for(int i=0; i<arr.listSize(); i++) {
        array[i] = arr.retreiveAt(i);
    }

    return *this;

}

template<typename e>
void ArrayList<e>::extend(const ArrayList<e>* arrayList) {
    for (int i = 0; i < arrayList->size(); i++) {
        this->insertEnd(arrayList->retrieveAt(i));
    }
}

template<typename e>
e ArrayList<e>::min() const {

    if(numOfElements == 0) {
        cout << "There are no elements in the array" << endl;
        return;
    }

    e min = this->retreiveAt(0);

    for(int i=0; i<numOfElements; i++) {
        if(this->retreiveAt(i) < min) {
            min = this->retreiveAt(i);
        }
    }
    return min;
}

template<typename e>
e ArrayList<e>::max() const {

    if(numOfElements == 0) {
        cout << "There are no elements in the array" << endl;
        return;
    }

    e max = this->retreiveAt(0);

    for(int i=0; i<numOfElements; i++) {
        if(this->retreiveAt(i) > max) {
            max = this->retreiveAt(i);
        }
    }
    return max;
}

template<typename e>
int ArrayList<e>::count(const e& element)  {

    if(numOfElements == 0) {
        return 0;
    }

    int count = 0;

    for(int i=0; i<numOfElements; i++) {
        if(this->retreiveAt(i) == element) {
            count++;
        }
    }
    return count;
}


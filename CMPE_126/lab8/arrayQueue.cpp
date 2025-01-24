#include <iostream>
#include "arrayQueue.hpp"

template <typename T>
arrayQueue<T>::arrayQueue() {
    size = 0;
    frontP = 0;
    backP = 0;
    capacity = 10;
    arr = new T[capacity];
}

template <typename T>
arrayQueue<T>::~arrayQueue() {
    size = 0;
    frontP = 0;
    backP = 0;
    delete[] arr;
}

template <typename T>
void arrayQueue<T>::enqueue(T element) {
    if(isFull()) {
        std::cout << "The queue is full" << std::endl;
    }
    arr[backP] = element;
    size++;
    backP = (backP+1)%capacity; 
}

template <typename T>
T arrayQueue<T>::dequeue() {
    if(isEmpty()) {
        std::cout << "There are no elements in queue" << std::endl;
    }
    T temp = arr[frontP];
    size--;
    frontP = (frontP+1)%capacity; 
    return temp;
}

template <typename T>
T arrayQueue<T>::front() {
    return arr[frontP];
}

template <typename T>
int arrayQueue<T>::getSize() {
    return size;
}

template <typename T>
int arrayQueue<T>::maxSize() {
    return capacity;
}

template <typename T>
bool arrayQueue<T>::isEmpty() {
    return size == 0;
}

template <typename T>
bool arrayQueue<T>::isFull() {
    return (size == capacity) && !(size == 0);
}
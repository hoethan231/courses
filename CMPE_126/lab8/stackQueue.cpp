#include <iostream>
#include "stackQueue.hpp"

template <typename T>
stackQueue<T>::stackQueue() {
    size = 0;
    capacity = 10;
}

template <typename T>
stackQueue<T>::~stackQueue() {
    size = 0;
    while(!stack1.empty()) {
        stack1.pop();
    }
}

template <typename T>
void stackQueue<T>::enqueue(T element) {
    if(isFull()) {
        std::cout << "The queue is full" << std::endl;
    }
    stack1.push(element);
    size++;
}

template <typename T>
T stackQueue<T>::dequeue() {
    if(isEmpty()) {
        std::cout << "There are no elements in queue" << std::endl;
    }
    while(!stack1.empty()) {
        stack2.push(stack1.top());
        stack1.pop();
    }
    T temp = stack2.top();
    stack2.pop();
    size--;
    while(!stack2.empty()) {
        stack1.push(stack2.top());
        stack2.pop();
    }
    return temp;
}

template <typename T>
T stackQueue<T>::front() {
    while(!stack1.empty()) {
        stack2.push(stack1.top());
        stack1.pop();
    }
    T temp = stack2.top();
    while(!stack2.empty()) {
        stack1.push(stack2.top());
        stack2.pop();
    }
    return temp;
}

template <typename T>
int stackQueue<T>::getSize() {
    return size;
}

template <typename T>
int stackQueue<T>::maxSize() {
    return capacity;
}

template <typename T>
bool stackQueue<T>::isEmpty() {
    return size == 0;
}

template <typename T>
bool stackQueue<T>::isFull() {
    return (size == capacity) && !(size == 0);
}
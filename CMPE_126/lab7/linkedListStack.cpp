#include <iostream>
#include "linkedListStack.hpp"

template <typename T>
Stack<T>::Stack() : size(0) {}

template <typename T>
Stack<T>::~Stack() {
    stack.clearList();
    size = 0;
}

template <typename T>
void Stack<T>::push(T) {
    stack->insertAt(0);
    size++;
}

template <typename T>
T Stack<T>::pop() {
    if(size == 0) {
        std::cout << "Cannot pop an empty stack" << std::endl;
    }
    stack->removeAt(0);
    size--;
}

template <typename T>
T Stack<T>::top() {
    if(size == 0) {
        std::cout << "Cannot top an empty stack" << std::endl;
    }
    stack->retrieveAt(0);
}

template <typename T>
void Stack<T>::clear() {
    stack->clearList();
}
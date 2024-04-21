#pragma once
#include "linkedList.hpp"

template <typename T>
class LinkedList;

template<typename T>
class Stack {

    public:
        Stack();
        ~Stack();
        void push(T);
        T pop();
        T top();
        void clear();
    private:
        LinkedList<T>* stack;
        int size;

};
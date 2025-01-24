#include <stack>
#pragma once

template <typename T>
class stackQueue {

    private:
        std::stack<T> stack1;
        std::stack<T> stack2;
        int size;
        int capacity;

    public:
        stackQueue();
        ~stackQueue();
        void enqueue(T);
        T dequeue();
        T front();
        int getSize();
        int maxSize();
        bool isEmpty();
        bool isFull();

};

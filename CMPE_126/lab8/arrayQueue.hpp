#pragma once

template <typename T>
class arrayQueue {

    private:
        T* arr;
        int size;
        int capacity;
        int frontP;
        int backP;

    public:
        arrayQueue();
        ~arrayQueue();
        void enqueue(T);
        T dequeue();
        T front();
        int getSize();
        int maxSize();
        bool isEmpty();
        bool isFull();

};
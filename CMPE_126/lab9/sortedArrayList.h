#include <iostream>
#pragma once

template <typename T>
class sortedArrayList {

    private:
        T arr[100];
        int size;
        int capacity;

    public:
        sortedArrayList();
        ~sortedArrayList();
        bool isEmpty() const;
        bool isFull() const;
        int listSize() const;
        int maxListSize() const;
        void print();
        bool insert(T);
        void remove(T);
        void clearList();
        unsigned int binarySearchIter(T);
        unsigned int binarySearchRec(T, int, int);

};
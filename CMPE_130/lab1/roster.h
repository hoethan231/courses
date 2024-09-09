#ifndef ROSTER_H
#define ROSTER_H
#include <iostream>
#include "student.h"

class Roster {

    private:
        int capacity;
        int size;
        Student* array;
        void expand();

    public:
        Roster();
        Roster(int);
        ~Roster();
        bool isEmpty();
        bool isFull();
        int getCapacity();
        int getSize();
        void insert(Student);
        void remove(Student);
        void update(Student, int, std::string, std::string, std::string);
        void printAll();
        void clear();
        void insertionSort();
        void selectionSort();
        int partition(int, int);
        void quickSort(int, int);

};

#endif
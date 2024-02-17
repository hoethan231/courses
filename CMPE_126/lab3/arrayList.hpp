#pragma once
#include <iostream>
using namespace std;

class ArrayList {

    private:

        int size;
        int numOfElements;
        int* array;
        void expand();

    public:

        ArrayList(); //
        ArrayList(int); //
        ~ArrayList();
        bool isEmpty() const; //
        bool isFull() const; //
        int listSize() const; //
        int maxListSize() const; //
        void print(); //
        bool isItemAtEqual(int, int);//
        void insertAt(int, int); //
        void insertEnd(int); // 
        void removeAt(int); //
        int retreiveAt(int); //
        void replaceAt(int, int); //
        void clearList();
        ArrayList& operator=(ArrayList&);

};
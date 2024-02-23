#pragma once
#include <iostream>
using namespace std;

template <typename e>
class ArrayList {

    private:

        int size;
        int numOfElements;
        e* array;
        void expand();

    public:

        ArrayList();
        ArrayList(int);
        ~ArrayList();
        bool isEmpty() const;
        bool isFull() const;
        int listSize() const;
        int maxListSize() const;
        void print();
        bool isItemAtEqual(int, e);//
        void insertAt(int, e);
        void insertEnd(e); 
        void removeAt(int);
        e retreiveAt(int);
        void replaceAt(int, e);
        void clearList();
        ArrayList& operator=(ArrayList&);

};
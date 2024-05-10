
#include <iostream>
using namespace std;
#pragma once
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
        bool isItemAtEqual(int, e);
        void insertAt(int, e);
        void insertEnd(e); 
        void removeAt(int);
        e retrieveAt(int) const;
        void replaceAt(int, e);
        void clearList();
        void extend(const ArrayList<e>*);
        e min() const;
        e max() const;      
        int count(const e&);  
        e findMinRecursive(ArrayList<e>, e);
        ArrayList& operator=(ArrayList&);
        unsigned int seqSearchIter(e);
        unsigned int seqSearchRec(e, int);

};
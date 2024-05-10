#include <iostream>
#include "arrayList.hpp"
using namespace std;
#pragma once

template <typename T>
class Node {   

    public:
        T data;
        Node<T>* next;
        Node();
        Node(T);
        Node(T, Node<T>*);
        ~Node();

};

template <typename T>
class LinkedList {

    protected:
        Node<T>* head;
        Node<T>* tail;
        int size;
        int capacity;

    public:
        LinkedList();
        ~LinkedList();
        bool isEmpty() const;
        bool isFull() const;
        int listSize() const;
        int maxListSize() const;
        void print();
        bool isItemAtEqual(int, T);
        void insertAt(int, T);
        void insertEnd(T);
        void removeAt(int);
        T retrieveAt(int);
        void replaceAt(int, T);
        void clearList();
        bool inBounds(int);
        void extend(const ArrayList<T>*);
        T min() const;
        T max() const;
        int count(const T&);
        T findMinRecursive(LinkedList<T>, T);
        LinkedList<T>& operator=(LinkedList<T>&);
        bool seqSearchIter(T);
        bool seqSearchRec(T, Node<T>*);

};
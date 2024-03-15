#include <iostream>
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
        T retreiveAt(int);
        void replaceAt(int, T);
        void clearList();
        bool inBounds(int);
        LinkedList<T>& operator=(LinkedList<T>&);

};
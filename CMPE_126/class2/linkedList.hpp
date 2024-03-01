#include <iostream>
using namespace std;
#pragma once

template <typename T>
class Node {

    private:
        T data;
        Node<T>* next;

    public:
        Node(T);
        Node(T, Node);

};

template <typename T>
class LinkedList {

    private:
        Node<T>* head, tail;
        int size;

    public:
        LinkedList();
        LinkedList(T[]);
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
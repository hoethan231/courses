#include <iostream>
using namespace std;
#pragma once

template <typename T>
class Node {

    private:
        T data;
        Node* next;

    public:
        Node(T);

};

class LinkedList {

    private:
        Node* head, tail;

    public:
        LinkedList();
        void print();

}
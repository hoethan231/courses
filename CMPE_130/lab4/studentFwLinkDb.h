#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "Node.h"

class StudentFwLinkDB {

    private: 
        int size;
        Node* student;

    public:
        StudentFwLinkDB();
        StudentFwLinkDB(Node);
        Node* split(Node*);
        Node* merge(Node* first, Node* second);
        Node* mergeSort();


};

#endif
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "student.h"

class Node {

    public:
        Student data;
        Node* next;
        Node();
        Node(Student, Node);
        friend std::ostream& operator<<(std::ostream&, const Node&);

};

#endif
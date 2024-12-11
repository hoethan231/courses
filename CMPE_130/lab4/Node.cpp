#include <iostream>
#include "Node.h"
#include "student.h"

Node::Node() {
    this->data = Student();
    this->next = nullptr;    
}

Node::Node(Student data, Node next) {
    this->data = data;
    this->next = &next;
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << node.data;
    return os;
}
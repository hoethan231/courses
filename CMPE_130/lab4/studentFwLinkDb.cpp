#include "studentFwLinkDb.h"
#include "Node.h"
#include <iostream>

StudentFwLinkDB::StudentFwLinkDB() {
    this->size = 0;
    this->student = &Node();
}

StudentFwLinkDB::StudentFwLinkDB(Node data) {
    this->size = 1;
    this->student = &data;
}

Node* StudentFwLinkDB::split(Node* student) {

    Node* fast = student;
    Node* slow = student;

    while(fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        if(fast != nullptr) {
            slow = slow->next;
        }
    }

    Node* temp = slow->next;
    slow->next = nullptr;
    return temp;
}

Node* StudentFwLinkDB::merge(Node* first, Node* second) {

    if(first == nullptr) {
        return second;
    }
    if(second == nullptr) {
        return first;
    }

    if(first->data->id < second->data->id) {
        first->next = merge(first->next, second);
        return first;
    }
    else {
        second->next = merge(second->next, first);
        return second;
    }
}

Node* StudentFwLinkDB::mergeSort() {

    if(this->student == nullptr || this->student->next == nullptr) {
        return this->student;
    }

    Node* half = this->split(this->student);

    Node* head = split(student);
    half = split(half);

    return merge(head, half);
}
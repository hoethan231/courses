#include <iostream>
#include "student.h"
#include "Node.h"
#include "studentFwLinkDb.h"

int main() {
    Student student1(1, "Alice", "Smith", "Sophomore");
    Student student2(2, "Bob", "Johnson", "Junior");
    Student student3(3, "Charlie", "Williams", "Senior");
    Student student4(4, "Diana", "Brown", "Freshman");

    Node node1(student1, nullptr);
    Node node2(student2, nullptr);
    Node node3(student3, nullptr);
    Node node4(student4, nullptr);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;

    StudentFwLinkDB db(node1);

    Node* sortedList = db.mergeSort();

    Node* current = sortedList;
    while (current != nullptr) {
        std::cout << current->data << std::endl;
        current = current->next;
    }

    return 0;
}
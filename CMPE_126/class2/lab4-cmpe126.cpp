#include "linkedList.cpp"
#include <iostream>
using namespace std;

int main() {
    
    LinkedList<int> list1{};
    LinkedList<string> list2{};

    list2.insertAt(0,"rawr");
    list2.insertAt(0,"blah");
    list2.insertAt(0, "ompf");

    cout << "Is list 1 empty: " << list1.isEmpty() << endl;
    cout << "Is list 2 empty: " << list2.isEmpty() << endl;
    cout << "Is list 1 full: " << list1.isFull() << endl;
    cout << "The size of list 1 is: " << list1.listSize() << endl;
    cout << "The size of list 2 is: " << list2.listSize() << endl << endl;

    list1.insertEnd(18);    
    list1.insertEnd(7);

    cout << "Is list1[0] == 18: " << list1.isItemAtEqual(0,18) << endl;
    cout << "Is list1[1] == 18: " << list1.isItemAtEqual(1,18) << endl << endl;
    
    list2.print();
    list2.removeAt(1);
    list2.print();
    list2.replaceAt(0, "womp");

    cout << "list2[1] is: " << list2.retreiveAt(1) << endl;

    list2.clearList();
    list2.print();

    LinkedList<int> list3{};

    list3 = list1;
    list3.print();

    sortedLinkedList<int> sorted{};

    sorted.insert(10);
    sorted.insert(6);
    sorted.insert(20);
    sorted.insert(100);
    sorted.insert(2);

    sorted.print();

    return 0;
}
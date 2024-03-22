#include <iostream>
#include "arrayList.hpp"
#include "linkedList.hpp"

int main() {

    ArrayList<int> arrList1;
    ArrayList<int> arrList2;
    LinkedList<int> linkedList1;

    arrList1.insertAt(0, 12);
    arrList1.insertAt(0, 23);
    arrList2.insertAt(0, 8);
    arrList1.insertAt(0, 12);
    arrList2.insertAt(0, 32);

    arrList2.extend(&arrList1);
    arrList2.print();
    cout << "The min is " << arrList2.min() << " and the max is " << arrList2.max() << endl;
    cout << "The count of 12 is " << arrList2.count(12) << endl;

    linkedList1.insertAt(0, 12);
    linkedList1.insertAt(0, 23);
    linkedList1.insertAt(0, 8);
    linkedList1.insertAt(0, 12);
    linkedList1.insertAt(0, 32);

    linkedList1.extend(&arrList1);
    linkedList1.print();
    cout << "The min is " << linkedList1.min() << " and the max is " << linkedList1.max() << endl;
    cout << "The count of 12 is " << linkedList1.count(12) << endl;

    return 0;
}
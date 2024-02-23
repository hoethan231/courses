#include <iostream>
#include "arrayList.cpp"

int main() {

    ArrayList<int> arr1;
    ArrayList<int> arr2(20);

    cout << endl << "Is array one empty: " << arr1.isEmpty() << endl;
    cout << "Is array one full: " << arr1.isFull() << endl << endl;
    
    arr1.insertEnd(5);
    arr1.insertAt(1,8);

    for(int i=0; i<10; i++) {
        arr1.insertEnd(i);
    }

    
    cout << "Array one list size: " << arr1.listSize() << endl;
    cout << "Array one max list size: " << arr1.maxListSize() << endl << endl;
    
    arr1.removeAt(5);

    arr1.replaceAt(0, 20);

    cout << "Array one: ";
    arr1.print();
    cout << "Is the 3rd item equal to 1: " << arr1.isItemAtEqual(2, 1) << endl;
    cout << "Is the 4th item equal to 1: " << arr1.isItemAtEqual(3, 1) << endl;
    cout << "The 7th item in array one is: " << arr1.retreiveAt(6) << endl << endl;

    arr2 = arr1;
    arr1.clearList();

    cout << "Array two: ";
    arr2.print();
    cout << "Array one: ";
    arr1.print();

    return 0;
}
//============================================================================
// Name        : Searching.cpp
// Author      : Mahima
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "./sortedArrayList.cpp"
#include "linkedList.cpp"
#include "arrayList.cpp"
using namespace std;

unsigned int choice = 0;
unsigned int val = 0;

int main() {

	ArrayList<int> arr;
	LinkedList<int> list;
	sortedArrayList<int> sArr;

	for(int i=0; i<10;i++) {
		arr.insertAt(0,i);
		list.insertAt(0,i);
		sArr.insert(i);
	}

	do {
	        cout << "Choose your search type:" << endl;
	        cout << "1. Arrays: Sequential Search without recursion" << endl;
	        cout << "2. Arrays: Sequential Search with recursion" << endl;
	        cout << "3. Ordered Arrays: Binary Search without recursion" << endl;
	        cout << "4. Ordered Arrays: Binary Search with recursion" << endl;
	        cout << "5. Linked List: Search without recursion"  << endl;
	        cout << "6. Linked List: Search with recursion" << endl;
	        cout << "Enter 0 to exit" << endl;
	        cout << "Your choice: ";

	        cin >> choice;

	        /****************************
	         * TODO: Implement what you will do with the choice.
	         *****************************/

	        cout<<"\nSpecify the element to be searched for: ";
			cin >> val;

		switch (choice)
		{
		case(1):
			cout << "The value: " << val << " is at index: " << arr.seqSearchIter(val) << endl;
			arr.print();
			cout << endl;
			break;
		case(2):
			cout << "The value: " << val << " is at index: " << arr.seqSearchRec(val, 0) << endl;
			arr.print();
			cout << endl;
			break;
		case(3):
			cout << "The value: " << val << " is at index: " << sArr.binarySearchIter(val) << endl;
			sArr.print();
			cout << endl;
			break;
		case(4):
			cout << "The value: " << val << " is at index: " << sArr.binarySearchRec(val, 0, 10) << endl;
			sArr.print();
			cout << endl;
			break;
		case(5):
			cout << "Is the value: " << val << " in the array: " << list.seqSearchIter(val) << endl;
			list.print();
			cout << endl;
			break;
		case(6):
			cout << "Is the value: " << val << " in the array: " << list.seqSearchRec(val, nullptr) << endl;
			list.print();
			cout << endl;
			break;
		default:
			break;
		}

	} while(choice!=0);
	return 0;
}

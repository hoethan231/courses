//============================================================================
// Name        : main.cpp
// Author      : Mahima
// Version     : 1
// Description : Queue implementation test. Comment out parts you do not need.
//============================================================================

#include <iostream>
#include "arrayQueue.cpp"
#include "stackQueue.cpp"
using namespace std;

int main() {
	try{
		std::cout << std::endl;
		arrayQueue<char> charQueue1;
		std::cout << "The capacity of the queue is " << charQueue1.maxSize() << " elements" << std::endl;
		std::cout << "Is the queue Empty: " << charQueue1.isEmpty() << std::endl;
		charQueue1.enqueue('A');
		charQueue1.enqueue('B');
		std::cout << "There are " << charQueue1.getSize() << " elements in the queue" << std::endl;
		std::cout << "Is the queue Empty: " << charQueue1.isEmpty() << std::endl;
		std::cout << "Is the queue Full: " << charQueue1.isFull() << std::endl;
		cout << charQueue1.dequeue() << endl;
		charQueue1.enqueue('C');
		cout << charQueue1.dequeue() << endl;
		charQueue1.enqueue('D');
		cout << charQueue1.dequeue() << endl;
		cout << charQueue1.dequeue() << endl;
		cout << charQueue1.dequeue() << endl;
	}
	catch(const char *e) {
		cout << e << endl;
	}
	
	try{
		stackQueue<char> charQueue2;
		charQueue2.enqueue('A');
		charQueue2.enqueue('B');
		cout << charQueue2.dequeue() << endl;
		charQueue2.enqueue('C');
		cout << charQueue2.dequeue() << endl;
		charQueue2.enqueue('D');
		cout << charQueue2.dequeue() << endl;
		cout << charQueue2.dequeue() << endl;
		cout << charQueue2.dequeue() << endl;
	}
	catch(const char *e) {
		cout << e << endl;
	}
	return 0;
}

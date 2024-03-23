#include <iostream>
#include "padovan.cpp"
#include "palindrome.cpp"
#include "arrayList.cpp"
#include "linkedList.cpp"

int main() {

    std::cout << "The padovan of 10 is: " << padovan(10) << std::endl;

    std::cout << "The padovan of 5 is: " << padovan(5) << std::endl << std::endl;
    std::cout << "The steps are: " << std::endl;

    padovanWithSteps(5);
    std::cout << std::endl;

    std::cout << "Is 5821285 a palindrome: " << check_palindrome(5821285) << std::endl;
    std::cout << "Is 123456 a palindrome: " << check_palindrome(123456) << std::endl;

    ArrayList<int> arr;
    LinkedList<int> list;
    arr.insertAt(0,10);
    arr.insertAt(0,5);
    arr.insertAt(0,11);
    arr.insertAt(0,20);
    arr.insertAt(0,8);
    list.insertAt(0,10);
    list.insertAt(0,5);
    list.insertAt(0,11);
    list.insertAt(0,20);
    list.insertAt(0,8);

    arr.print();
    list.print();

    std::cout << "The min in the array is: " << arr.findMinRecursive(arr, 100) << std::endl;
    std::cout << "The min in the list is: " << list.findMinRecursive(list, 100) << std::endl;

    return 0;
}
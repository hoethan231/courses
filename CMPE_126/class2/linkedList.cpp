#include "linkedList.hpp"
#include <iostream>
using namespace std;

template <typename T>
Node<T>::Node(T data) : data(data), next(nullptr) {}

template <typename T>
Node<T>::Node(T data, Node next) : data(data), next(next) {}

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(T arr[]) {
    for(T element : arr) {
        insertEnd(element);
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    delete head;
    delete tail;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
bool LinkedList<T>::isFull() const {

    

}

template <typename T>
int LinkedList<T>::listSize() const {
    return size;
}

template <typename T>
int LinkedList<T>::maxListSize() const {
    
}

template <typename T>
void LinkedList<T>::print() {  
    Node<T>* curr = head;
    while(curr != nullptr) {
        cout << curr->data << " ~~ ";
        curr = curr->next;
    }
}

template <typename T>
bool LinkedList<T>::isItemAtEqual(int i, T element) {
    
    if(inBounds(i)) {
        Node<T>* curr = head;
        for(int j = 0; j < i; j++) {
            curr = curr->next;
        }

        return element.equals(curr->data);
    }
    
    cout << "index not in bounds";
    return false;
}

template <typename T>
void LinkedList<T>::insertAt(int i, T element) {

    if(inBounds(i)) {
        if(i == 0) {
            head = new Node(element);
        }
        else if(i == size){
            insertEnd(element);
        }
        else {
            Node<T>* curr = head;
            for(int j = 0; j < i-1; j++) {
                curr = curr->next;
            }
            Node newNode = new Node(element, curr->next);
            curr->next = newNode;
        }
        size++;
    }
    cout << "index not in bounds";
}

template <typename T>
void LinkedList<T>::insertEnd(T element) {
    
    Node<T>* curr = head;
    while(curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = new Node(element);
    tail = curr->next;
    size++;

}

template <typename T>
void LinkedList<T>::removeAt(int i) {
    
    if(inBounds(i)) {
        Node<T>* curr = head;
        for(int j = 0; j < i-1; j++) {
            curr = curr->next;
        }
        curr->next = curr->next->next;
        size--;
    }
    cout << "index out of bounds";
}

template <typename T>
T LinkedList<T>::retreiveAt(int i) {
    
    if(inBounds(i)) {
        Node<T>* curr = head;
        for(int j = 0; j < i; j++) {
            curr = curr->next;
        }
        return curr->data;
    }
    cout << "index out of bounds";
}

template <typename T>
void LinkedList<T>::replaceAt(int i, T element) {
    
    if(inBounds(i)) {
        Node<T>* curr = head;
        for(int j = 0; j < i; j++) {
            curr = curr->next;
        }
        curr->data = element;
    }
    cout << "index of out bounds";
}

template <typename T>
void LinkedList<T>::clearList() {
    
    while(head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

template <typename T>
bool LinkedList<T>::inBounds(int i) {
    return (i >= 0 && i <= size);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& list) {

    clearList()
    size = list.listSize();

    Node<T>* curr = list.head;
    while(curr != nullptr) {
        insertEnd(curr->data);
        curr = curr->next;
    }

    return *this;

}
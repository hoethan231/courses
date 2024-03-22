#include "linkedList.hpp"
#include "sortedLinkedList.hpp"
#include <iostream>
using namespace std;

template <typename T>
Node<T>::Node() : data(T()), next(nullptr) {}

template <typename T>
Node<T>::Node(T data) : data(data), next(nullptr) {}

template <typename T>
Node<T>::Node(T data, Node<T>* next) : data(data), next(next) {}

template <typename T>
Node<T>::~Node() {}

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0), capacity(100) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clearList();
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
bool LinkedList<T>::isFull() const {
    return size == capacity;
}

template <typename T>
int LinkedList<T>::listSize() const {
    return size;
}

template <typename T>
int LinkedList<T>::maxListSize() const {
    return capacity;
}

template <typename T>
void LinkedList<T>::print() {  
    Node<T>* curr = head;
    while(curr != nullptr) {
        cout << curr->data << " ~~ ";
        curr = curr->next;
    }
    cout << endl;
}

template <typename T>
bool LinkedList<T>::isItemAtEqual(int i, T element) {
    
    if(inBounds(i)) {
        Node<T>* curr = head;
        for(int j = 0; j < i; j++) {
            curr = curr->next;
        }

        return curr->data == element;
    }
    else {
        cout << "index not in bounds" << endl;
    }
    
    return false;
}

template <typename T>
void LinkedList<T>::insertAt(int i, T element) {
    if (inBounds(i)) {
        if (i == 0) {
            head = new Node<T>(element, head);
            if (size == 0) {
                tail = head;
            }
        } else if (i == size) {
            insertEnd(element);
        } else {
            Node<T>* curr = head;
            for (int j = 0; j < i - 1; j++) {
                curr = curr->next;
            }
            Node<T>* newNode = new Node<T>(element, curr->next);
            curr->next = newNode;
            if (curr->next->next == nullptr) {
                tail = curr->next;
            }
        }
        size++;
    } else {
        cout << "Index not in bounds" << endl;
    }
}

template <typename T>
void LinkedList<T>::insertEnd(T element) {
    if(head == nullptr) {
        insertAt(0, element);
    }
    else {
        tail->next = new Node<T>(element);
        tail = tail->next;
        size++;
    }

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
    else {
        cout << "index out of bounds" << endl;
    }
    
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
    else {
        cout << "index out of bounds" << endl;
    }
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
    else {
        cout << "index of out bounds" << endl;
    }
    
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

    clearList();
    size = list.listSize();
    Node<T>* curr = list.head;
    while(curr != nullptr) {
        insertEnd(curr->data);
        curr = curr->next;
    }

    return *this;

}

template <typename T>
void sortedLinkedList<T>::insert(T element) {
    Node<T>* newNode = new Node<T>(element);

    if (this->head == nullptr || element <= this->head->data) {
        newNode->next = this->head;
        this->head = newNode;
        if (this->tail == nullptr) {
            this->tail = this->head;
        }
        return;
    }

    Node<T>* curr = this->head;
    while (curr->next != nullptr && curr->next->data < element) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    if (newNode->next == nullptr) {
        this->tail = newNode;
    }
}

template<typename T>
void LinkedList<T>::extend(const ArrayList<T>* arr) {
    for (int i = 0; i < arr->size(); i++) {
        this->insertEnd(arr->retrieveAt(i));
    }
}

template<typename T>
T LinkedList<T>::min() const {
    if (size == 0) {
        cout << "There are no elements in the list" << endl;
    }

    T min = this->head->data;
    Node<T>* temp = this->head;
    while (temp != nullptr) {
        if (temp->data < min) {
            min = temp->data;
        }
        temp = temp->next;
    }
    return min;
}

template<typename T>
T LinkedList<T>::max() const {
    if (size == 0) {
        cout << "There are no elements in the list" << endl;
    }

    T max = this->head->data;
    Node<T>* temp = this->head;
    while (temp != nullptr) {
        if (temp->data > max) {
            max = temp->data;
        }
        temp = temp->next;
    }
    return max;
}

template<typename T>
int LinkedList<T>::count(const T& element) {
    int count = 0;
    Node<T>* temp = this->head;
    while (temp != nullptr) {
        if (temp->data == element) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

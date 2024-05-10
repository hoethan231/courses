#include "sortedArrayList.h"

template <typename T>
sortedArrayList<T>::sortedArrayList() {
    size = 0;
    capacity = 100;
}

template <typename T>
sortedArrayList<T>::~sortedArrayList() {
    size = 0;
    delete[] arr;
}

template <typename T>
bool sortedArrayList<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
bool sortedArrayList<T>::isFull() const {
    return size == capacity;
}

template <typename T>
int sortedArrayList<T>::listSize() const {
    return size;
}

template <typename T>
int sortedArrayList<T>::maxListSize() const {
    return capacity;
}

template <typename T>
void sortedArrayList<T>::print() {
    for(int i=0; i<size; i++) {
        std::cout << arr[i] << " ";
    }
}

template <typename T>
bool sortedArrayList<T>::insert(T element) {

    if (isEmpty()) {
        arr[0] = element;
        size++;
        return true;
    }

    int insertPos = 0;
    while (insertPos < size && arr[insertPos] < element) {
        insertPos++;
    }

    for (int i = size; i > insertPos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[insertPos] = element;
    size++;

    return true;
}

template <typename T>
void sortedArrayList<T>::remove(T element) {
    if (isEmpty()) {
        return;
    }

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        std::cout << "Element not found in the list." << std::endl;
        return;
    }

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
    std::cout << "Element removed successfully." << std::endl;
}


template <typename T>
void sortedArrayList<T>::clearList() {
    size = 0;
}

template <typename T>
unsigned int sortedArrayList<T>::binarySearchIter(T val) {
    
    int low = 0;
    int high = size-1;

    while(high >= low) {
        int mid = low + ((high-low)/2);
        if(arr[mid] == val) {
            return mid;
        }

        if(arr[mid] > val) {
            high = mid-1;
        }
        else {
            low = mid+1;
        }
    }

    return -1;
}

template <typename T>
unsigned int sortedArrayList<T>::binarySearchRec(T val, int low, int high) {

    if(high >= low) {
        int mid = low + ((high-low)/2);
    
        if(arr[mid] == val) {
            return mid;
        }

        if(arr[mid] >= val) {
            return binarySearchRec(val, low, mid-1);
        }
        else {
            return binarySearchRec(val, mid+1, high);
        }
    }

    return -1;

}
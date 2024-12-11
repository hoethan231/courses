
arr = [2,8,5,1,4,9,3,7,6]

def swap(i,j) -> None:
    arr[i], arr[j] = arr[j], arr[i]
        
def selectionSort(arr):
    for i in range(len(arr)):
        minNum = i
        for j in range(i, len(arr)):
            if arr[minNum] > arr[j]:
                minNum = j
        if arr[i] > arr[minNum]:
            swap(i, minNum)

def insertionSort(arr):
    for i in range(len(arr)):
        j = i
        while j > 0 and arr[j] < arr[j-1]:
            swap(j, j-1)
            j -= 1

def bubbleSort(arr):
    for i in range(len(arr)):
        for j in range(0, len(arr)-i-1):
            if arr[j] > arr[j+1]:
                swap(j, j+1)

def mergeSort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        mergeSort(L)
        mergeSort(R)

        i = j = k = 0

        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
        
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1
        
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

def quickSort(arr, left, right):
    if left < right:
        partitionIdx = partition(arr, left, right)
        quickSort(arr, left, partitionIdx - 1)
        quickSort(arr, partitionIdx + 1, right)
    
def partition(arr, left, right):
    i, j = left, right-1
    pivot = arr[right]
    while i < j:
        while i < len(arr) and arr[i] < pivot:
            i += 1
        while j < len(arr) and arr[j] > pivot:
            j -= 1
        if i < j:
            arr[i], arr[j] = arr[j], arr[i]
    
    if arr[i] > pivot:
        arr[i], arr[right] = arr[right], arr[i]
    return i    

def heapSort(arr):
    maxHeap(arr)
    for i in range(len(arr)-1, 0, -1):
        swap(0, i)
        heapify(arr,i, 0)

def maxHeap(arr):
    for i in range(len(arr)//2-1, -1, -1):
        heapify(arr,len(arr), i)

def heapify(arr, n, i):
    left, right = 2*i+1, 2*i+2
    maxIdx = i
    if left < n and arr[left] < arr[i]:
       maxIdx = left
    if right < n and arr[right] < arr[i]:
       maxIdx = right
    
    if maxIdx != i:
        swap(maxIdx, i)
        heapify(arr,n, maxIdx)
     

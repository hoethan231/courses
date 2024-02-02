/* Ethan Ho
 * Sorting
 * A program that obtains the execution time of selection sort, merge sort, quick sort, heap sort, and radix sort for input sizes of 50,000, 100,000, 150,000, 200,000, 250,000, and 300,000
 * I should have made a seperate class for each method initially but instead swapped to classes after making 4 methods already, please do not mind the messey work
 */

public class Sorting {
    
    public static void main(String[] args) {

        double[] fifty = new double[50000];
        populate(fifty);
        double[] hundred = new double[100000];
        populate(hundred);
        double[] hundredFifty = new double[150000];
        populate(hundredFifty);
        double[] twoHundred = new double[200000];
        populate(twoHundred);
        double[] twofifty = new double[250000];
        populate(twofifty);
        double[] threeHundred = new double[300000];
        populate(threeHundred);
        
        System.out.println("");
        System.out.println("Array size  |  Selection  Merge  Quick  Heap  Radix");
        System.out.println("---------------------------------------------------");
        System.out.println("   50,000   |    " + getTime(fifty, 1) + "       " + getTime(fifty, 2) + "    " + getTime(fifty, 3) + "   " + getTime(fifty, 4) + "    " + getTime(fifty, 5) + "  ");
        System.out.println("  100,000   |    " + getTime(fifty, 1) + "       " + getTime(fifty, 2) + "    " + getTime(fifty, 3) + "   " + getTime(fifty, 4) + "    " + getTime(fifty, 5) + "  ");
        System.out.println("  150,000   |    " + getTime(fifty, 1) + "       " + getTime(fifty, 2) + "    " + getTime(fifty, 3) + "   " + getTime(fifty, 4) + "    " + getTime(fifty, 5) + "  ");
        System.out.println("  200,000   |    " + getTime(fifty, 1) + "       " + getTime(fifty, 2) + "    " + getTime(fifty, 3) + "   " + getTime(fifty, 4) + "    " + getTime(fifty, 5) + "  ");
        System.out.println("  250,000   |    " + getTime(fifty, 1) + "       " + getTime(fifty, 2) + "    " + getTime(fifty, 3) + "   " + getTime(fifty, 4) + "    " + getTime(fifty, 5) + "  ");
        System.out.println("  300,000   |    " + getTime(fifty, 1) + "       " + getTime(fifty, 2) + "   " + getTime(fifty, 3) + "   " + getTime(fifty, 4) + "    " + getTime(fifty, 5) + "  ");

    }

    //populates the given array
    public static void populate(double[] arr) {

        for(int i = 0; i < arr.length - 1; i++) {
            arr[i] = (Math.random() * 100);
        }
    }

    //Returns the miliseconds of the given array and sorting method
    public static long getTime(double[] arr, int sortingMethod) {

        //SelectionS Sort
        if(sortingMethod == 1) {
            double[] test = new double[arr.length];
            System.arraycopy(arr, 0, test, 0, arr.length);
            long startTime = System.currentTimeMillis();
            SelectionSort(test);
            long endTime = System.currentTimeMillis();
            return endTime - startTime;
        }

        //MergeSort
        else if(sortingMethod == 2) {
            double[] test = new double[arr.length];
            System.arraycopy(arr, 0, test, 0, arr.length);
            long startTime = System.currentTimeMillis();
            MergeSort(test);
            long endTime = System.currentTimeMillis();
            return endTime - startTime;
        }

        //Quick Sort
        else if(sortingMethod == 3) {
            double[] test = new double[arr.length];
            System.arraycopy(arr, 0, test, 0, arr.length);
            long startTime = System.currentTimeMillis();
            SelectionSort(test);
            long endTime = System.currentTimeMillis();
            return endTime - startTime;
        }

        //Heap Sort
        else if(sortingMethod == 4) {
            double[] test = new double[arr.length];
            System.arraycopy(arr, 0, test, 0, arr.length);
            long startTime = System.currentTimeMillis();
            SelectionSort(test);
            long endTime = System.currentTimeMillis();
            return endTime - startTime;
        }

        //Radix Sort
        else{
            double[] test = new double[arr.length];
            System.arraycopy(arr, 0, test, 0, arr.length);
            long startTime = System.currentTimeMillis();
            RadixSort.sort(test);
            long endTime = System.currentTimeMillis();
            return endTime - startTime;
        }
    
    }

    public static void SelectionSort(double[] arr) {

        for(int i = 0; i < arr.length - 1; i++) {

            double currentMin = arr[i];
            int currentMinIdx = i;

            for(int j = i; j < arr.length; j++) {

                if(currentMin > arr[j]) {
                    currentMin = arr[i];
                    currentMinIdx = j;
                }
            }

            if(currentMinIdx != i) {
                arr[currentMinIdx] = arr[i];
                arr[i] = currentMin;

            }
        }
    }

    public static void MergeSort(double[] arr) {

        if(arr.length > 1) {

            //mergesort the first half
            double[] firstHalf = new double[arr.length / 2];
            System.arraycopy(arr, 0, firstHalf, 0, arr.length / 2);
            MergeSort(firstHalf);

            //mergesort the second half
            int secondHalfLength = arr.length - arr.length / 2;
            double[] secondHalf = new double[secondHalfLength];
            System.arraycopy(arr, arr.length / 2, secondHalf, 0, secondHalfLength);
            MergeSort(secondHalf);

            merge(firstHalf, secondHalf, arr);
        }
    }

    public static void merge(double[] arr1, double[] arr2, double[] temp) {
        int currentOne = 0;
        int currentTwo = 0;
        int currentThree = 0;
        
        while (currentOne < arr1.length && currentTwo < arr2.length) {
            if (arr1[currentOne] < arr2[currentTwo]) {
                temp[currentThree++] = arr1[currentOne++];
            }
            else {
                temp[currentThree++] = arr2[currentTwo++];
        }
        
        while (currentOne < arr1.length) {
            temp[currentThree++] = arr1[currentOne++];
        }

        while (currentTwo < arr2.length)
            temp[currentThree++] = arr2[currentTwo++];
        }
        
    }

    public static void QuickSort(double[] arr) {
        quickSort(arr, 0, arr.length - 1);
    }


    public static void quickSort(double[] arr, int first, int last) {
        while (first < last) {
            int pivotIndex = partition(arr, first, last);
            if (pivotIndex - first < last - pivotIndex) {
                quickSort(arr, first, pivotIndex - 1);
                first = pivotIndex + 1;
            } else {
                quickSort(arr, pivotIndex + 1, last);
                last = pivotIndex - 1;
            }
        }
    }


    public static int partition(double[] arr, int first, int last) {

        double pivot = arr[first];
        int low = first + 1; // Index for forward search
        int high = last; // Index for backward search

        while (high > low) {
            // Search forward from left
            while (low <= high && arr[low] <= pivot) {low++;}

            // Search backward from right
            while (low <= high && arr[high] > pivot) {high--;}

            // Swap two elements in the arr
            if (high > low) {
                double temp = arr[high];
                arr[high] = arr[low];
                arr[low] = temp;
            }
        }

        while (high > first && arr[high] >= pivot) {high--;}

        // Swap pivot with arr[high]
        if (pivot > arr[high]) {
            arr[high] = pivot;
            return high;
        }
        else {
            return first;
        }
        
    }

    public static <E extends Comparable<E>> void HeapSort(E[] list) {

        Heap<E> heap = new Heap<>();

        for(int i = 0; i < list.length; i++) {
            heap.add(list[i]);
        }

        for(int i = list.length - 1; i >= 0; i--) {
            list[i] = heap.remove();
        }

    }

}

class Heap<E extends Comparable<E>> {
    private java.util.ArrayList<E> list = new java.util.ArrayList<>();

    /** Create a default heap */
    public Heap() {
    }

    /** Create a heap from an array of objects */
    public Heap(E[] objects) {
        for (int i = 0; i < objects.length; i++) {
            add(objects[i]);
        }
    }

    /** Add a new object into the heap */
    public void add(E newObject) {
        list.add(newObject); // Append to the heap
        int currentIndex = list.size() - 1; // The index of the last node

        while (currentIndex > 0) {
            
        int parentIndex = (currentIndex - 1) / 2;

        // Swap if the current object is greater than its parent
        if (list.get(currentIndex).compareTo(list.get(parentIndex)) > 0) {
            E temp = list.get(currentIndex);
            list.set(currentIndex, list.get(parentIndex));
            list.set(parentIndex, temp);
        }

        else {break;}

        currentIndex = parentIndex;
        }
    }

    /** Remove the root from the heap */
    public E remove() {
        if (list.size() == 0) {return null;}

    E removedObject = list.get(0);
    list.set(0, list.get(list.size() - 1));
    list.remove(list.size() - 1);

    int currentIndex = 0;
    while (currentIndex < list.size()) {
        int leftChildIndex = 2 * currentIndex + 1;
        int rightChildIndex = 2 * currentIndex + 2;

        // Find the maximum between two children
        if (leftChildIndex >= list.size()) {break;} // The tree is a heap
        int maxIndex = leftChildIndex;
        if (rightChildIndex < list.size()) {
            if (list.get(maxIndex).compareTo(list.get(rightChildIndex)) < 0) {
            maxIndex = rightChildIndex;
            }
        }


        // Swap if the current node is less than the maximum
        if (list.get(currentIndex).compareTo(list.get(maxIndex)) < 0) {
            E temp = list.get(maxIndex);
            list.set(maxIndex, list.get(currentIndex));
            list.set(currentIndex, temp);
            currentIndex = maxIndex;
        }

        else {break;} // The tree is a heap
    }

    return removedObject;

    }

    /** Get the number of nodes in the tree */
    public int getSize() {
        return list.size();
    }

}

class RadixSort {
    public static void sort(double[] array) {
        RadixSort.sort(array, 10);
    }

    public static void sort(double[] array, double radix) {
        if (array.length == 0) {
            return;
        }

        // Determine minimum and maximum values
        double minValue = array[0];
        double maxValue = array[0];
        for (int i = 1; i < array.length; i++) {
            if (array[i] < minValue) {
                minValue = array[i];
            } else if (array[i] > maxValue) {
                maxValue = array[i];
            }
        }

        // Perform counting sort on each exponent/digit, starting at the least
        // significant digit
        double exponent = 1;
        while ((maxValue - minValue) / exponent >= 1) {
            RadixSort.countingSortByDigit(array, radix, exponent, minValue);
            exponent *= radix;
        }
    }

    private static void countingSortByDigit(
            double[] array, double radix, double exponent, double minValue) {
        int bucketIndex;
        int[] buckets = new int[(int) radix];
        double[] output = new double[array.length];


        for (int i = 0; i < radix; i++) {
            buckets[i] = 0;
        }


        for (int i = 0; i < array.length; i++) {
            bucketIndex = (int) (((array[i] - minValue) / exponent) % radix);
            buckets[bucketIndex]++;
        }


        for (int i = 1; i < radix; i++) {
            buckets[i] += buckets[i - 1];
        }


        for (int i = array.length - 1; i >= 0; i--) {
            bucketIndex = (int) (((array[i] - minValue) / exponent) % radix);
            output[--buckets[bucketIndex]] = array[i];
        }


        for (int i = 0; i < array.length; i++) {
            array[i] = output[i];
        }
    }
}

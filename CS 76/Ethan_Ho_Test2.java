/* Ethan Ho 
 * Test 2 Program: Merge Sort
 * Two generic methods of merge sort
 */

import java.util.Comparator;

public class Ethan_Ho_Test2 {

    public static void main(String[] args) {

        Integer[] list = {2, 3, 2, 5, 6, 1, -2, 3, 14, 12};
        mergeSort(list);
        for (Integer num : list) {
            System.out.print(num + " ");
        }
        System.out.println();

        Circle[] list1 = {new Circle(2), new Circle(3), new Circle(2),
                new Circle(5), new Circle(6), new Circle(1), new Circle(2),
                new Circle(3), new Circle(14), new Circle(12)};
        mergeSort(list1, new CircleComparator());
        for (Circle ob : list1) {
            System.out.print(ob + " ");
        }
        System.out.println();
    }

    public static <E extends Comparable<E>> void mergeSort(E[] arr) {
        if (arr.length > 1) {
            int middle = arr.length / 2;

            E[] leftSide = (E[]) new Comparable[middle];
            System.arraycopy(arr, 0, leftSide, 0, middle);
            mergeSort(leftSide);

            E[] rightSide = (E[]) new Comparable[arr.length - middle];
            System.arraycopy(arr, middle, rightSide, 0, arr.length - middle);
            mergeSort(rightSide);

            merge(leftSide, rightSide, arr);
        }
    }

    public static <E extends Comparable<E>> void merge(E[] left, E[] right, E[] arr) {
        int current1 = 0;
        int current2 = 0;
        int current3 = 0;

        while (current1 < left.length && current2 < right.length) {
            if (left[current1].compareTo(right[current2]) <= 0) {
                arr[current3++] = left[current1++];
            } else {
                arr[current3++] = right[current2++];
            }
        }

        while (current1 < left.length) {
            arr[current3++] = left[current1++];
        }

        while (current2 < right.length) {
            arr[current3++] = right[current2++];
        }
    }

    public static <E> void mergeSort(E[] list, Comparator<? super E> comparator) {
        if (list.length > 1) {
            int mid = list.length / 2;
            E[] left = (E[]) new Object[mid];
            System.arraycopy(list, 0, left, 0, mid);
            mergeSort(left, comparator);

            E[] right = (E[]) new Object[list.length - mid];
            System.arraycopy(list, mid, right, 0, list.length - mid);
            mergeSort(right, comparator);

            merge(list, left, right, comparator);
        }
    }

    public static <E> void merge(E[] list, E[] left, E[] right, Comparator<? super E> comparator) {
        int current1 = 0;
        int current2 = 0;
        int current3 = 0;

        while (current1 < left.length && current2 < right.length) {
            if (comparator.compare(left[current1], right[current2]) <= 0) {
                list[current3++] = left[current1++];
            } else {
                list[current3++] = right[current2++];
            }
        }

        while (current1 < left.length) {
            list[current3++] = left[current1++];
        }

        while (current2 < right.length) {
            list[current3++] = right[current2++];
        }
    }

    static class Circle {
        private double radius;

        public Circle(double radius) {
            this.radius = radius;
        }

        public double getRadius() {
            return radius;
        }

        @Override
        public String toString() {
            return "r: " + radius;
        }
    }

    static class CircleComparator implements Comparator<Circle> {
        @Override
        public int compare(Circle one, Circle two) {
            return Double.compare(one.getRadius(), two.getRadius());
        }
    }
}

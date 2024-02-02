/* Ethan Ho
 * Implementing List
 * Revising Listing 24.5 on MyLinkedList.java and tests each of its methods
 */
import java.util.*;

public class ImplementingLists {
    
    public static void main(String[] args) {

        String[] namez = {"Amy", "Ant", "Yeji", "Ethan", "Phuc", "Amesters", "PluslePink", "Dragonitus", "Phuji", "Icydragons1357"};
        MyLinkedList names = new MyLinkedList(namez);

        System.out.println(" ");

        System.out.println("The list of names:                " + names.toString());
        System.out.println("The first element is:             " + names.getFirst());
        System.out.println("The last element is:              " + names.getLast());
        names.addFirst("John");
        System.out.println("The list with John first:         " + names.toString());
        names.addLast("Jimmy");
        System.out.println("The list with Jimmy last:         " + names.toString());
        names.removeFirst();
        System.out.println("The list without John first:      " + names.toString());
        names.removeLast();
        System.out.println("The list without Jimmy last:      " + names.toString());
        names.remove(1);
        System.out.println("The list index without 1 (Phuji): " + names.toString());
        System.out.println("Does the list contain Ethan?:     " + names.contains("Ethan"));
        System.out.println("Does the list contain Phuji?:     " + names.contains("Phuji"));
        System.out.println("The name at index 4 is:           " + names.get(4));
        names.add(3, "Yeji");
        System.out.println("Current lsit:                     " + names.toString());
        System.out.println("Yeji first appears at:            " + names.indexOf("Yeji"));
        System.out.println("Yeji lastly appears at:           " + names.lastIndexOf("Yeji"));
        names.set(1, "Dragon");
        System.out.println("Dragonitus is now Dragon:         " + names.toString());
        System.out.println("The size of the List is:          " + names.size());
        names.clear();
        System.out.println("The empty list is now:            " + names.toString());

        System.out.println(" ");
    }

}

class Node<E> {
    E element;
    Node<E> next;

    public Node(E e) {
        element = e;
    }
}

class MyLinkedList<E> implements List<E> {

    private Node<E> head, tail;
    private int size = 0;

    public MyLinkedList() {

    }

    public MyLinkedList(E[] objects) {
        for(E object : objects) {
            add(object);
        }
    }

    public E getFirst() {
        return size == 0 ? null : head.element;
    }

    public E getLast() {
        return size == 0 ? null : tail.element;
    }

    public void addFirst(E e) {

        Node<E> newNode = new Node<>(e);
        newNode.next = head;
        head = newNode;
        size++;

        if(tail == null) {tail = head;}

    }

    public void addLast(E e) {
        
        Node<E> newNode = new Node<>(e);
        if(tail == null) { head = tail = newNode; }
        else {
            tail.next = newNode;
            tail = newNode;
        }

    } 

    //Not part of the original code but added as this is an inherited abstract method
    @Override
    public boolean add(E e) {
        addFirst(e);
        return true;
    }

    @Override
    public void add(int index, E e) {
        
        if(index == 0) { addFirst(e); }
        else if(index >= size) { addLast(e); }
        else {
            Node<E> current = head;
            for(int i = 1; i < index; i++) {
                current = current.next;
            }
            Node<E> temp = current.next;
            current.next = new Node<>(e);
            (current.next).next = temp;
            size++;
        }
    }

    public E removeFirst() {

        if(size == 0) { return null; }
        else {
            Node<E> temp = head;
            head = head.next;
            size--;
            if(head == null) { tail = null; }
            return temp.element;
        }

    }

    public E removeLast() {

        if (size == 0) { return null; }
        else if (size == 1) {
            Node<E> temp = head;
            head = tail = null;
            size = 0;
            return temp.element;
        }
        else {
            Node<E> current = head;
            for(int i = 0; i < size - 2; i++) {
                current = current.next;
            }
            Node<E> temp = tail;
            tail = current;
            tail.next = null;
            size--;
            return temp.element;
        }

    }

    @Override
    public E remove(int index) {

        if(index < 0 || index >= size) { return null; }
        else if(index == 0) { removeFirst(); }
        else if(index == size - 1) { removeLast(); }
        else {
            Node<E> previous = head;
            for(int i = 1; i < index; i++) {
                previous = previous.next;
            }
            Node<E> current = previous.next;
            previous.next = current.next;
            size--;
            return current.element;
        }
        return null;

    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder("[");

        Node<E> current = head;
        while(current != null) {
            result.append(current.element);
            current = current.next;
            result.append(", ");
        }
        result.append("]");

        return result.toString();
    }

    @Override
    public void clear() {
        size = 0;
        head = tail = null;
    }

    @Override
    public boolean contains(Object e) {
        
        Node<E> current = head;
        while(current != null) {
            if(current.element == e) { return true; }
            current = current.next;
        }
        return false;
    }

    @Override
    public E get(int index) {

        if(index < 0 || index >= size) { return null; }
        else if(index == 0) { return head.element; }
        else if(index == size - 1) { return tail.element; }
        else {
            Node<E> current = head;
            for(int i = 1; i < index; i++) {
                current = current.next;
            }
            return current.element;
        }

    }

    @Override
    public int indexOf(Object e) {
        int index = 0;
        Node<E> current = head;

        //checks the head
        if (Objects.equals(current.element, e)) {
            return 0;
        }

        while (current != null) {
            if (Objects.equals(current.element, e)) { return index; }
            index++;
            current = current.next;
        }

        return -1;
    }


    @Override
    public int lastIndexOf(Object e) {

        int index = 0;
        int lastIndex = -1;
        Node<E> current = head;

        //checks the head
        if(current.element == e) { return 0; }

        while(current != null) {
            if(current.element == e) {
                lastIndex = index;
            }
            index++;
            current = current.next;
        }

        return lastIndex;
    }

    public E set(int index, E e) {

        Node<E> current = head;
        
        for(int i = 0; i < index; i++) {
            current = current.next;
        }
        current.element = e;

        return null;
    }

    @Override
    public class LinkedListIterator implements java.util.Iterator<E> {
        private Node<E> current = head;

        @Override
        public boolean hasNext() {
            return (current != null);
        }

        @Override
        public E next() {
            E e = current.element;
            current = current.next;
            return e;
        }

        @Override
        public void remove() {

            if(current == null) { return; }
            if(current == head) { head = head.next; }
            else {
                Node<E> previous = head;
                while (previous.next != current) {
                    previous = previous.next;
                }
                previous.next = current.next;
            }

            if(current == tail) {
                tail = current == head ? null : head;
            }

            current = current.next;
            size--;
        }

    }

    private static class Node<E> {
        E element;
        Node<E> next;

        public Node(E element) {
            this.element = element;
        }
    }

    @Override
    public int size() {
        return size;
    }

}




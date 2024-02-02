/* Ethan Ho 
 * Binary Search Trees
 * Fully implement the BST class in Listing 25.4 as well as a driver program to test every method
 */
import java.util.*;

public class BinarySearchTree {
    
    public static void main(String[] args) {

        BST<Integer> bst = new BST<>();

        // Test insert method
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.insert(3);
        bst.insert(7);
        bst.insert(12);
        bst.insert(18);


        // Test search method
        System.out.println("Searching for 5: " + bst.search(5));
        System.out.println("Searching for 8: " + bst.search(8));

        // Test size method
        System.out.println("Size of the tree: " + bst.getSize());

        // Test inorder traversal
        System.out.print("Inorder Traversal: ");
        bst.inorder();
        System.out.println();

        // Test preorder traversal
        System.out.print("Preorder Traversal: ");
        bst.preorder();
        System.out.println();

        // Test postorder traversal
        System.out.print("Postorder Traversal: ");
        bst.postorder();
        System.out.println();

        // Test delete method
        System.out.println("Deleting 5: " + bst.delete(5));
        System.out.println("Deleting 8: " + bst.delete(8));

        // Test size method after delete
        System.out.println("Size of the tree after delete: " + bst.getSize());

        // Test iterator
        System.out.print("Inorder Traversal using Iterator: ");
        for (Integer value : bst) {
            System.out.print(value + " ");
        }
        System.out.println();

        // Test toArray method
        Object[] array = bst.toArray();
        System.out.print("Array representation of the tree: ");
        for (Object value : array) {
            System.out.print(value + " ");
        }
        System.out.println();

        // Test clear method
        bst.clear();
        System.out.println("Size of the tree after clearing: " + bst.getSize());
    
    }
}


interface Tree<E> extends Collection<E> {

    public boolean search(E e);

    public boolean insert(E e);

    public boolean delete(E e);

    public int getSize();

    public default void inorder() {   
    }

    public default void postorder(){
    }

    public default void preorder() {
    }

    @Override
    public default boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public default boolean contains(Object e) {
        return search((E)e);
    }

    @Override
    public default boolean add(E e) {
        return insert(e);
    }

    @Override
    public default boolean remove(Object e) {
        return delete((E)e);
    }

    @Override
    public default int size() {
        return getSize();
    }

    @Override 
    public default boolean containsAll(Collection<?> c) {
        
        Iterator<?> iter = c.iterator();
        while(iter.hasNext()) {
            if(!contains(iter.next())) { return false; }
        }

        return true;
        
    }

    @Override
    public default boolean addAll(Collection<? extends E> c) {

        Iterator<?> iter = c.iterator();
        while(iter.hasNext()) {
            add((E)iter.next());
        }

        return true;

    }

    @Override
    public default boolean removeAll(Collection<?> c) {

        Iterator<?> iter = c.iterator();
        while(iter.hasNext()) {
            remove((E)iter.next());
        }

        return true;

    }

    @Override
    public default boolean retainAll(Collection<?> c) {
        boolean modified = false;

        for(E e : this) {
            if(!(c.contains(e))) {
                remove(e);
                modified = true;
            }
        }

        return modified;

    }

    @Override
    public default Object[] toArray() {
        Object[] arr = new Object[size()];
        int index = 0;

        for(E e : this) {
            arr[index++] = e;
        }

        return arr;
    }

    @Override
    public default <T> T[] toArray(T[] array) {
        int size = size();
        
        if (array.length < size) {
            array = (T[]) java.lang.reflect.Array.newInstance(array.getClass().getComponentType(), size);
        }
        
        int index = 0;
        for (E e : this) {
            array[index++] = (T) e;
        }

        if (array.length > size) {
            array[size] = null;
        }

        return array;
    }


}


class BST<E extends Comparable<E>> implements Tree<E> {
    protected TreeNode<E> root;
    protected int size = 0;

    public BST() {
    }

    public BST(E[] objects) {
        for(E e : objects) {
            add(e);
        }
    }

    @Override
    public boolean search(E e) {
        TreeNode<E> current = root;

        while(current != null) {
            if(e.compareTo(current.element) < 0) {
                current = current.left;
            }
            else if(e.compareTo(current.element) > 0) {
                current = current.right;
            }
            else {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean insert(E e) {
        if (root == null) {
            root = createNewNode(e);
            size++;
            return true;
        }

        TreeNode<E> parent = null;
        TreeNode<E> current = root;
        while (current != null) {
            if (e.compareTo(current.element) < 0) {
                parent = current;
                current = current.left;
            } else if (e.compareTo(current.element) > 0) {
                parent = current;
                current = current.right;
            } else {
                return false;
            }
        }

        if (e.compareTo(parent.element) < 0) {
            parent.left = createNewNode(e);
        } else {
            parent.right = createNewNode(e);
        }

        size++;
        return true;
    
    }

    protected TreeNode<E> createNewNode(E e) {
        return new TreeNode<>(e);
    }

    @Override
    public void inorder() {
        inorder(root);
    }

    protected void inorder(TreeNode<E> root) {
        if(root == null) { return; }
        inorder(root.left);
        System.out.print(root.element + " ");
        inorder(root.right);
    }

    @Override
    public void postorder() {
        postorder(root);
    }

    protected void postorder(TreeNode<E> root) {
        if(root == null) { return; }
        inorder(root.left);
        inorder(root.right);
        System.out.print(root.element + " ");
    }

    @Override
    public void preorder() {
        preorder(root);
    }

    protected void preorder(TreeNode<E> root) {
        if(root == null) { return; }
        System.out.print(root.element + " ");
        inorder(root.left);
        inorder(root.right);
    }

    public static class TreeNode<E> {
        protected E element;
        protected TreeNode<E> left;
        protected TreeNode<E> right;

        public TreeNode(E e) {
            element = e;
        }
    }

    @Override
    public int getSize() {
        return size;
    }

    public TreeNode<E> getRoot() {
        return root;
    }

    public java.util.ArrayList<TreeNode<E>> path(E e) {
        java.util.ArrayList<TreeNode<E>> list = new java.util.ArrayList<>();
        TreeNode<E> current = root;

        while(current != null) {
            list.add(current);
            if(e.compareTo(current.element) < 0) {
                current = current.left;
            }
            else if(e.compareTo(current.element) > 0) {
                current = current.right;
            }
            else {
                break;
            }
        }

        return list;
    }

    @Override
    public boolean delete(E e) {
        TreeNode<E> parent = null;
        TreeNode<E> current = root;

        while(current != null) {
            if(e.compareTo(current.element) < 0) {
                parent = current;
                current = current.left;
            }
            else if(e.compareTo(current.element) > 0) {
                parent = current;
                current = current.right;
            }
            else {
                break;
            }
        }

        if(current == null) {
            return false;
        }

        if(current.left == null) {
            if(parent == null) {
                root = current.right;
            }
            else {
                if(e.compareTo(parent.element) < 0) {
                    parent.left = current.right;
                }
                else {
                    parent.right = current.right;
                }
            }
        }
        else {
            TreeNode<E> parentOfRightMost = current;
            TreeNode<E> rightMost = current.left;

            while(rightMost.right != null) {
                parentOfRightMost = rightMost;
                rightMost = rightMost.right;
            }
            current.element = rightMost.element;

            if(parentOfRightMost.right == rightMost) {
                parentOfRightMost.right = rightMost.left;
            }
            else {
                parentOfRightMost.left = rightMost.left;
            }
        }

        size--;
        return true;
    }

    @Override
    public java.util.Iterator<E> iterator() {
        return new InorderIterator();
    }

    private class InorderIterator implements java.util.Iterator<E> {
        private java.util.ArrayList<E> list = new java.util.ArrayList<>();
        private int current = 0;

        public InorderIterator() {
            inorder();   
        }

        private void inorder() {
            inorder(root);
        }

        private void inorder(TreeNode<E> root) {
            if(root == null) { return; }
            inorder(root.left);
            list.add(root.element);
            inorder(root.right);
        }

        @Override
        public boolean hasNext() {
            if(current < list.size()) {
                return true;
            }
            return false;
        }

        @Override
        public E next() {
            return list.get(current++);
        }

        @Override public void remove() {
            if(current == 0) {
                throw new IllegalStateException();
            }
            delete(list.get(--current));
            list.clear();
            inorder();
        }
    }

    @Override
    public void clear() {
        root = null;
        size = 0;
    }


}

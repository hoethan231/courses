
import java.util.*;

public class TreesExtraCrdit {

    public static void main(String[] args) {
        ArrayList<Integer> nums = new ArrayList<>();
        AVLTree<Integer> avl = new AVLTree<>();
        BST<Integer> bst = new BST<>();

        for (int i = 0; i < 500000; i++) {
            nums.add(i);
        }

        // test twice
        for (int i = 1; i < 3; i++) {
            Collections.shuffle(nums);
            int randomInt = (int) Math.random() * 100 + 1;

            long avlTime = System.currentTimeMillis();
            for (Integer integer : nums) {
                avl.insert(integer); // insert test
            }
            avl.search(randomInt); // search test
            avl.clear(); // delete test
            long avlEndTime = System.currentTimeMillis() - avlTime;

            long bstTime = System.currentTimeMillis();
            for (Integer integer : nums) {
                bst.insert(integer); // insert test
            }
            bst.search(randomInt); // search test
            bst.clear(); // delete test
            long bstEndTime = System.currentTimeMillis() - bstTime;

            System.out.println("Test " + i + "\nAVL Tree: " + avlEndTime + " milliseconds" + "\nBST Tree: " + bstEndTime + " milliseconds");
        }
    }

}

interface Tree<E> extends Collection<E> {

    public boolean search(E e);

    public boolean insert(E e);

    public boolean delete(E e);

    public int getSize();

    public default void inorder() {
    }

    public default void postorder() {
    }

    public default void preorder() {
    }

    @Override
    public default boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public default boolean contains(Object e) {
        return search((E) e);
    }

    @Override
    public default boolean add(E e) {
        return insert(e);
    }

    @Override
    public default boolean remove(Object e) {
        return delete((E) e);
    }

    @Override
    public default int size() {
        return getSize();
    }

    @Override
    public default boolean containsAll(Collection<?> c) {

        Iterator<?> iter = c.iterator();
        while (iter.hasNext()) {
            if (!contains(iter.next())) {
                return false;
            }
        }

        return true;

    }

    @Override
    public default boolean addAll(Collection<? extends E> c) {

        Iterator<?> iter = c.iterator();
        while (iter.hasNext()) {
            add((E) iter.next());
        }

        return true;

    }

    @Override
    public default boolean removeAll(Collection<?> c) {

        Iterator<?> iter = c.iterator();
        while (iter.hasNext()) {
            remove((E) iter.next());
        }

        return true;

    }

    @Override
    public default boolean retainAll(Collection<?> c) {
        boolean modified = false;

        for (E e : this) {
            if (!(c.contains(e))) {
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

        for (E e : this) {
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
        for (E e : objects) {
            add(e);
        }
    }

    @Override
    public boolean search(E e) {
        TreeNode<E> current = root;

        while (current != null) {
            if (e.compareTo(current.element) < 0) {
                current = current.left;
            } else if (e.compareTo(current.element) > 0) {
                current = current.right;
            } else {
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
        if (root == null) {
            return;
        }
        inorder(root.left);
        System.out.print(root.element + " ");
        inorder(root.right);
    }

    @Override
    public void postorder() {
        postorder(root);
    }

    protected void postorder(TreeNode<E> root) {
        if (root == null) {
            return;
        }
        inorder(root.left);
        inorder(root.right);
        System.out.print(root.element + " ");
    }

    @Override
    public void preorder() {
        preorder(root);
    }

    protected void preorder(TreeNode<E> root) {
        if (root == null) {
            return;
        }
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

        while (current != null) {
            list.add(current);
            if (e.compareTo(current.element) < 0) {
                current = current.left;
            } else if (e.compareTo(current.element) > 0) {
                current = current.right;
            } else {
                break;
            }
        }

        return list;
    }

    @Override
    public boolean delete(E e) {
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
                break;
            }
        }

        if (current == null) {
            return false;
        }

        if (current.left == null) {
            if (parent == null) {
                root = current.right;
            } else {
                if (e.compareTo(parent.element) < 0) {
                    parent.left = current.right;
                } else {
                    parent.right = current.right;
                }
            }
        } else {
            TreeNode<E> parentOfRightMost = current;
            TreeNode<E> rightMost = current.left;

            while (rightMost.right != null) {
                parentOfRightMost = rightMost;
                rightMost = rightMost.right;
            }
            current.element = rightMost.element;

            if (parentOfRightMost.right == rightMost) {
                parentOfRightMost.right = rightMost.left;
            } else {
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
            if (root == null) {
                return;
            }
            inorder(root.left);
            list.add(root.element);
            inorder(root.right);
        }

        @Override
        public boolean hasNext() {
            if (current < list.size()) {
                return true;
            }
            return false;
        }

        @Override
        public E next() {
            return list.get(current++);
        }

        @Override
        public void remove() {
            if (current == 0) {
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

class AVLTree<E extends Comparable<E>> extends BST<E> {

    public AVLTree() {
    }

    public AVLTree(E[] objects) {
        super(objects);
    }

    @Override
    protected AVLTreeNode<E> createNewNode(E e) {
        return new AVLTreeNode<E>(e);
    }

    @Override
    public boolean insert(E e) {
        boolean modified = super.insert(e);
        if (!modified) {
            return false;
        } else {
            balancePath(e);
        }
        return true;

    }

    private void updateHeight(AVLTreeNode<E> node) {
        if (node.left == null && node.right == null) {
            node.height = 0;
        } else if (node.left == null) {
            node.height = 1 + ((AVLTreeNode<E>) (node.right)).height;
        } else if (node.right == null) {
            node.height = 1 + ((AVLTreeNode<E>) (node.left)).height;
        } else {
            node.height = 1
                    + Math.max((((AVLTreeNode<E>) (node.right)).height), (((AVLTreeNode<E>) (node.left)).height));
        }
    }

    private void balancePath(E e) {
        java.util.ArrayList<TreeNode<E>> path = path(e);

        for (int i = path.size() - 1; i >= 0; i--) {
            AVLTreeNode<E> A = (AVLTreeNode<E>) (path.get(i));
            updateHeight(A);
            AVLTreeNode<E> parentOfA = (A == root) ? null : (AVLTreeNode<E>) (path.get(i - 1));

            switch (balanceFactor(A)) {

                case -2:
                    if (balanceFactor((AVLTreeNode<E>) A.left) <= 0) {
                        balanceLL(A, parentOfA);
                    } else {
                        balanceLR(A, parentOfA);
                    }
                    break;

                case +2:
                    if (balanceFactor((AVLTreeNode<E>) A.right) >= 0) {
                        balanceRR(A, parentOfA);
                    } else {
                        balanceRL(A, parentOfA);
                    }

            }
        }
    }

    private int balanceFactor(AVLTreeNode<E> node) {
        if (node.right == null) {
            return -node.height;
        } else if (node.left == null) {
            return +node.height;
        } else {
            return (((AVLTreeNode<E>) node.right).height) - (((AVLTreeNode<E>) node.left).height);
        }
    }

    private void balanceLL(TreeNode<E> A, TreeNode<E> parentOfA) {
        TreeNode<E> B = A.left;

        if (A == root) {
            root = B;
        } else {
            if (parentOfA.left == A) {
                parentOfA.left = B;
            } else {
                parentOfA.right = B;
            }
        }

        A.left = B.right;
        B.right = A;
        updateHeight((AVLTreeNode<E>) A);
        updateHeight((AVLTreeNode<E>) B);
    }

    private void balanceLR(TreeNode<E> A, TreeNode<E> parentOfA) {
        TreeNode<E> B = A.left;
        TreeNode<E> C = B.right;

        if (A == root) {
            root = C;
        } else {
            if (parentOfA.left == A) {
                parentOfA.left = C;
            } else {
                parentOfA.right = C;
            }
        }

        A.left = C.right;
        B.right = C.left;
        C.left = B;
        C.right = A;

        updateHeight((AVLTreeNode<E>) A);
        updateHeight((AVLTreeNode<E>) B);
        updateHeight((AVLTreeNode<E>) C);

    }

    private void balanceRR(TreeNode<E> A, TreeNode<E> parentOfA) {
        TreeNode<E> B = A.right;

        if (A == root) {
            root = B;
        } else {
            if (parentOfA.left == A) {
                parentOfA.left = B;
            } else {
                parentOfA.right = B;
            }
        }

        A.right = B.left;
        B.left = A;

        updateHeight((AVLTreeNode<E>) A);
        updateHeight((AVLTreeNode<E>) B);

    }

    private void balanceRL(TreeNode<E> A, TreeNode<E> parentOfA) {
        TreeNode<E> B = A.right;
        TreeNode<E> C = B.left;

        if (A == root) {
            root = C;
        } else {
            if (parentOfA.left == A) {
                parentOfA.left = C;
            } else {
                parentOfA.right = C;
            }
        }

        A.right = C.left;
        B.left = C.right;
        C.left = A;
        C.right = B;

        updateHeight((AVLTreeNode<E>) A);
        updateHeight((AVLTreeNode<E>) B);
        updateHeight((AVLTreeNode<E>) C);

    }

    @Override
    public boolean delete(E element) {
        if (root == null) {
            return false;
        }

        TreeNode<E> parent = null;
        TreeNode<E> current = root;

        while (current != null) {
            if (element.compareTo(current.element) < 0) {
                parent = current;
                current = current.left;
            } else if (element.compareTo(current.element) > 0) {
                parent = current;
                current = current.right;
            } else {
                break;
            }
        }

        if (current == null) {
            return false;
        }
        if (current.left == null) {

            if (parent == null) {
                root = current.right;
            } else {
                if (element.compareTo(parent.element) < 0) {
                    parent.left = current.right;
                } else {
                    parent.right = current.right;
                }

                balancePath(parent.element);
            }
        } else {
            TreeNode<E> parentOfRightMost = current;
            TreeNode<E> rightMost = current.left;

            while (rightMost.right != null) {
                parentOfRightMost = rightMost;
                rightMost = rightMost.right;
            }

            current.element = rightMost.element;
            if (parentOfRightMost.right == rightMost) {
                parentOfRightMost.right = rightMost.left;
            } else {
                parentOfRightMost.right = rightMost.left;
            }

            balancePath(parentOfRightMost.element);
        }

        size--;
        return true;

    }

    protected static class AVLTreeNode<E> extends BST.TreeNode<E> {
        protected int height = 0;

        public AVLTreeNode(E e) {
            super(e);
        }
    }
}
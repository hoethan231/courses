/* Ethan Ho
 * Generics, ArrayList Sorter
 * A programs that sorts an arraylist of either int, double, or String
 */

public class Generics {
    
    public static void main(String[] args) {

        Integer[] integers = {new Integer(2), new Integer(4), new Integer(3)};
        Double[] doubles = {new Double(3.4), new Double(-12.3), new Double(1.2)};
        String[] String = {new String("Bob"), new String("Alice"), new String("Ted"), new String("Carol")};

        System.out.println("Integers:");
        sort(integers);
        print(integers);
        System.out.println("Doubles:");
        sort(doubles);
        print(doubles);
        System.out.println("Strings:");
        sort(String);
        print(String);

    }

    //uses a nested for loop to individually sort each slot
    public static <E extends Comparable<E>> void sort(E[] arr) {
        E least;
        int leastIdx;

        for(int i = 0; i < arr.length; i++) {
            least = arr[i];
            leastIdx = i;

            for(int j = i + 1; j < arr.length; j++) {
                if(least.compareTo(arr[j])> 0) {
                    least = arr[j];
                    leastIdx = j;
                }
            }

            if(leastIdx != i) {
                arr[leastIdx] = arr[i];
                arr[i] = least;

            }
        }
    }

    //based off the textbook for printing each object in a list
    public static <E> void print(E[] arr) {
        for(E obj : arr) {
            System.out.print(obj + " ");
        }
        System.out.println("");
    }
}

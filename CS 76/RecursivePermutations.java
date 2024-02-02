/* Ethan Ho
 * Recursion II, String Permutation
 * A program that recursivly displays all permutations of the string
 */import java.util.Scanner;

public class RecursivePermutations {

    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);
        System.out.println("Please enter your String!: ");
        displayPermutation(input.next());


    }

    //begins the recursion 
    public static void displayPermutation(String s) {

        displayPermutation("",s);

    }

    public static void displayPermutation(String s1, String s2) {
        //base case
        if(s2.isEmpty()) {
            System.out.println(s1);
        }
        //recursivly inputs char from s2 to s1
        else {
            for(int i = 0; i < s2.length(); i++) {
                displayPermutation(s1 + s2.charAt(i), s2.substring(0,i) + s2.substring(i + 1));
            }
        }
        
    }

}
/* Ethan Ho
 * Recursion I, ReverseString
 * A program that hopfully uses effecient memory to reverse the order of a string with a helper method
 */
import java.util.Scanner;

public class ReverseString {
    
    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);
        System.out.println("Please enter a String!: ");
        
        reverseDisplay(input.nextLine());
    }

    //Enters the String into the 
    public static void reverseDisplay(String value) {
        System.out.println("");
        System.out.println("Reverse: ");
        reverseDisplay(value, value.length()-1);
    }

    //Contains the base case
    public static void reverseDisplay(String value, int high) {
        if(high >= 0) {
            System.out.print(value.charAt(high));
            reverseDisplay(value,high-1);
        }
    }   
}

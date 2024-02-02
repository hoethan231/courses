/* Ethan Ho 
 * Test 1 Program: Character Count
 * Uses recursion to count the instances of a char occuring within the given array
 */
import java.util.Scanner;;

public class Test1Program {
    
    public static void main(String[] args) {

        char[ ] test = {'T', 'h', 'i', 's', 'i', 's', 't', 'h', 'e', 's', 't', 't', 'i', 'n', 'g'};
        CharacterCounter(test);

    }

    public static void CharacterCounter(char[] chars) {

        Scanner input = new Scanner(System.in);
        System.out.println("Input a character: ");
        System.out.println(charCount(chars, 0, input.next().charAt(0)));
        
    }

    public static int charCount(char[] array, int start, char ch) {

        //base case
        if(start == array.length) {
            return 0;
        }

        //counts the current idx and then calls the mthod to check the next
        if(array[start] == ch) {
            return 1 + charCount(array, start + 1, ch);
        }

        return charCount(array, start + 1, ch);
    }
}

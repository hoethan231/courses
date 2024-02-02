/* Ethan Ho
 * Sets and Maps
 * Count the occurrences of words in a text file
 */ 
import java.util.*;
import java.io.*;

public class SetsAndMaps {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length != 1) {
            System.out.println("Usage: java CountOccurrenceOfWords fullfilename");
            System.exit(1);
        }

        String filename = args[0];
        File file = new File(filename);
        if (!file.exists()) {
            System.out.println("The file " + filename + " does not exist.");
            System.exit(1);
        }

        Map<String, Integer> dictionary = new TreeMap<>();

        try (Scanner input = new Scanner(file)) {
            while (input.hasNext()) {
                String[] words = input.nextLine().split("[ ,;.:?()\\[\\]\n\t\r]+");
                countKeywords(dictionary, words);
            }
        }

        displayWordCounts(dictionary);
    }

    public static void countKeywords(Map<String, Integer> dictionary, String[] words) {
        for (String word : words) {
            String toStore = word.toLowerCase();

            if (toStore.length() > 0 && Character.isLetter(toStore.charAt(0))) {
                dictionary.put(toStore, dictionary.getOrDefault(toStore, 0) + 1);
            }
        }
    }

    public static void displayWordCounts(Map<String, Integer> dictionary) {
        System.out.println("Display words and their count in ascending order of the words");
        for (Map.Entry<String, Integer> entry : dictionary.entrySet()) {
            System.out.println(entry.getValue() + "\t" + entry.getKey());
        }
    }
}

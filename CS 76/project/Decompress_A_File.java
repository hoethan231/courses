/* {Justin Dam & Ethan Ho, part 1}, {Aakarsh Pasi & Terry Zou, part 2}
 * Programming Project Part 2
 * Decompress a previously compressed file so that it replicates the original source file in Part I
 */

 import java.io.*;

 public class Decompress_A_File {
 
     public static void main(String[] args) throws Exception{
         if (args.length != 2) {
             System.out.println("Usage: java Decompress_a_File <compressedFile> <outputFile>");
             System.exit(1);
         }
               
         String inputFile = args[0];
         String outputFile = args[1];
 
         File file = new File(inputFile);
         if (!file.exists()) { // check if file exists
             System.out.println("The file " + inputFile + " does not exist.");
             System.exit(1);
         }
 
         try {
           /*read a file*/
           ObjectInputStream input = new ObjectInputStream(new FileInputStream(inputFile));
           String[] codes = (String[]) input.readObject(); // codes stores the Huffman codes
           
           // read the binary contents from the compressed file
           int nextByte;
             String codeString = "";
             while (input.available() > 0) {
                 nextByte = input.read();
                 String padding = "";
                 int marker = 128;
                 while (nextByte < marker) {
                     padding += "0";
                     marker /= 2;
                 }
                 codeString += (padding + Integer.toBinaryString(nextByte));
             }
           input.close();
           
           /*write a file*/
           BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile)); 
             while (codeString.length() > 0) {
               for (int j = 0; j < codes.length; j++) {
                   if (codes[j] != null && 
                      codes[j].length() <= codeString.length()) {
                       String sub = codeString.substring(0, codes[j].length());
                       if (codes[j].equals(sub)) {
                           writer.write((char) j);
                           codeString = codeString.substring(
                                   codes[j].length());
                           j = 0;
                       }
                   }
               }
               break;
             }
             writer.close();
           System.out.println("Decompressed successfully!");
           } catch (IOException e) {
               System.out.println("Your file cannot be decompressed due to error: " + e.getMessage());
           }
     }
 }
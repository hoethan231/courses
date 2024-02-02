/* Ethan Ho
 * File I/O
 * Implementing a class called BitOutputStream that writes a stream of bits to a file
 */ 


import java.io.*;

public class Program2 {
    public static void main(String[] args) throws Exception {

        BitOutputStream output = new BitOutputStream(new File("testOutput.dat"));
        output.writeBit("010000100100001001101");
        output.close();
        System.out.println("Done!");

    }

    public static class BitOutputStream {
        private FileOutputStream output;
        private byte currentByte;
        private int bitsDone;

        public BitOutputStream(File file) throws IOException {
            output = new FileOutputStream(file);
            bitsDone = 0;
            currentByte = 0;

        }

        public void writeBit(String bitString) throws IOException {
            for(int i = 0; i < bitString.length(); i++) {
                writeBit(bitString.charAt(i));
            }
        }

        public void writeBit(char bit) throws IOException {
            currentByte = (byte)(currentByte << 1);
            currentByte += (bit == '0' ? 0 : 1);
            if(++bitsDone >= 8) {
                output.write(currentByte);
                currentByte = 0;
                bitsDone = 0;
            }
        }

        public void close() throws IOException {
            while (bitsDone != 0) {
                writeBit('0');
            }
            output.close();
        }

    }


}

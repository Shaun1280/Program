package Java_Code.Tutorial.Expections;

import java.io.*;

public class ReadFile_Demo {
    public static void main(String[] args) {
        FileReader fr = null;
        try {
            File file = new File("file.txt");
            fr = new FileReader(file);
            char[] a = new char[50];
            fr.read(a);
            for (char c : a) {
                System.out.print(c);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                fr.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }
}

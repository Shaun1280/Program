package Java_Code.Tutorial.Expections;

import java.io.*;

public class Try_withDemo {
    public static void main(String[] args) {
        try(FileReader fr = new FileReader("E://file.txt")) {
            char []a = new char[50];
            fr.read(a);
            for (char c : a) System.out.print(c);
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}

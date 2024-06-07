package Java_Code.Tutorial;

import java.util.*;

public class TimeTest {

    public static void main (String[] args) {
        try {
            long start = System.currentTimeMillis();
            System.out.println(new Date() + "\n");

            Thread.sleep(5 * 60 * 10); //3000ms = 3s
            System.out.println(new Date() + "\n");

            long end = System.currentTimeMillis();
            long diff = end - start;
            System.out.println(diff + "\n");
        } catch (Exception e) {
            System.out.println("Got an exception!");
        }
    }
}
package Java_Code.Tutorial;

import java.util.*;

public class CommandLine {
    public static void main(String[] args) {
        int cnt = 0;
        if (args.length == 0)
            System.out.println("No args");
        for (String str : args) {
            System.out.println("args[" + (++cnt) + "]:" + str);
        }
    }
}

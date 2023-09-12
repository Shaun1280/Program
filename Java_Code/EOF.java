

import java.util.*;

public class EOF {
    public static final int MAXN = 100000;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int num = 0;
        while (sc.hasNext())
            System.out.println(++num + " " + sc.nextLine());
        sc.close();
    }
}
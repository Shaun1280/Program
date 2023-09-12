package Java_Code.Tutorial;

import java.util.*;

class FreshJuice {
    enum FreshJuiceSize { SMALL, MEDIUM, LARGE};
    FreshJuiceSize size;
}


public class Enum {
    public static void main(String args[]) {
        FreshJuice juice = new FreshJuice();
        juice.size = FreshJuice.FreshJuiceSize.MEDIUM;
        System.out.println("Size: " + juice.size);
    }
}
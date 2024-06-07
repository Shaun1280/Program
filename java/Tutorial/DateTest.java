package Java_Code.Tutorial;

import java.util.Date;
import java.text.*;

public class DateTest {
    public static void main(String args[]) {
        // Instantiate a Date object
        Date date = new Date();
        SimpleDateFormat ft = new SimpleDateFormat("E yyyy.MM.dd 'at ' hh:mm:ss a zzz");

        System.out.println("Current Date: " + ft.format(date));

        // display time and date
        String str = String.format("Current Date/Time : %tc", date );
        System.out.printf(str);
    }
};
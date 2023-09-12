package BigInteger;

import java.util.*;
import java.math.*;

public class Binary_search {
  public static BigInteger x, m;
  public static String s;

  public static boolean check(long mid) {
    BigInteger sum = BigInteger.ZERO;
    for (int i = 0; i < s.length(); i++) {
      sum = sum.multiply(BigInteger.valueOf(mid)).add(BigInteger.valueOf(s.charAt(i) - '0'));
      if (sum.compareTo(m) == 1)
        return false;
    }
    return true;
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    x = in.nextBigInteger();
    m = in.nextBigInteger();
    s = x.toString();
    if (s.length() == 1 && x.compareTo(m) <= 0) {
      System.out.println(1);
      in.close();
      return;
    }
    long n = s.charAt(0) - '0' + 1;
    for (int i = 0; i < s.length(); i++) {
      if ((long) (s.charAt(i) - '0' + 1) > n)
        n = (long) (s.charAt(i) - '0' + 1);
    }
    long l = n, r = (long) 1E18, ans = l - 1;
    while (l <= r) {
      long mid = (l + r) / 2;
      if (check(mid) == true) {
        l = mid + 1;
        ans = mid;
      } else
        r = mid - 1;
    }
    System.out.println(ans - n + 1);
    in.close();
  }
}

package BigInteger;

//https://vjudge.net/contest/262550#problem/F
import java.util.*;
import java.math.*;

public class Triangle {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    BigInteger a[] = new BigInteger[101];
    a[0] = BigInteger.valueOf(0);
    a[1] = BigInteger.valueOf(4);
    a[2] = BigInteger.valueOf(14);
    for (int i = 3; i <= 100; i++)
      a[i] = a[i - 1].multiply(BigInteger.valueOf(4)).subtract(a[i - 2]);
    int tc = in.nextInt();
    while ((tc--) != 0) {
      BigInteger n = in.nextBigInteger();
      for (int i = 0; i < 100; i++) {
        if (n.compareTo(a[i]) == 1 && n.compareTo(a[i + 1]) < 1) {
          System.out.println(a[i + 1]);
          break;
        }
      }
    }
    in.close();
  }
}

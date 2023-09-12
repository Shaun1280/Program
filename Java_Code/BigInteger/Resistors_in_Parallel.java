package BigInteger;

import java.util.*;
import java.math.*;

public class Resistors_in_Parallel {

  static boolean isprime(int x) {
      for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
      return true;
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int tc = in.nextInt();
    for (int i = 1; i <= tc; i++) {
      BigInteger n = in.nextBigInteger(), tmp = BigInteger.ONE;
      Vector<Integer> vec = new Vector<Integer>();

      for (int j = 2; j <= 250; j++) {
          if (isprime(j) == true) {
            if ((tmp.multiply(BigInteger.valueOf(j))).compareTo(n) == 1) break;
            tmp = tmp.multiply(BigInteger.valueOf(j));
            vec.add(j);
          }
      }

      BigInteger p = BigInteger.ONE, q = BigInteger.ONE;
      for (int j = 0; j < vec.size(); j++) {
        p = p.multiply(BigInteger.valueOf(vec.get(j) + 1));
        q = q.multiply(BigInteger.valueOf(vec.get(j)));
      }

      BigInteger gcd = p.gcd(q);
      p = p.divide(gcd);
      q = q.divide(gcd);
      System.out.print(q + "/" + p + "\n");
    }
    in.close();
  }
}
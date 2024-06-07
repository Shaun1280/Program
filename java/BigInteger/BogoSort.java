package BigInteger;

//big integer mul div gcd
import java.util.*;
import java.math.*;

public class BogoSort {
    public static final int MAXN = 100000 + 5;

    public static void main(String[] args) throws Exception {
        int to[] = new int[MAXN], vis[] = new int[MAXN];
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for (int i = 1; i <= n; i++)
            to[i] = in.nextInt();
        BigInteger ans = BigInteger.ONE;
        ans = in.nextBigInteger();
        for (int i = 1; i <= n; i++) {
            if (vis[i] == 1)
                continue;
            int cnt = 0, cur = i;
            while (vis[cur] == 0) {
                vis[cur] = 1;
                cnt++;
                cur = to[cur];
            }
            ans = ans.multiply(BigInteger.valueOf(cnt).divide(ans.gcd(BigInteger.valueOf(cnt))));
        }
        in.close();
        System.out.println(ans);
    }
}
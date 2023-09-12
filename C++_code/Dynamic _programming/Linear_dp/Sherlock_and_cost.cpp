#include <bits/stdc++.h>
const int MAXN = 1e5 + 1;
using namespace std;
int dp[MAXN][1], T, n, B[MAXN];
inline int read() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x;
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    T = read();
    // A[i] must be 1 or B[i] to make S maximum |1-x| > (|2-x)|>|1-(x-1)|
    while (T--) {
        n = read();
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) B[i] = read();
        /*dp[][1]: consider B[] as 1*/
        /*dp[][1]: do not consider B[] as 1*/
        /*10 1 10 1 max_conditon B[0]=10, B[1]=1, B[2]=10, B[3]=1*/
        for (int i = 1; i < n; i++)
            dp[i][1] = max(dp[i - 1][1] + abs(1 - 1),
                           dp[i - 1][0] + abs(1 - B[i - 1])),
            /*consider B[i]=1, B[i-1]=1 or B[i-1]!=1*/
                dp[i][0] = max(dp[i - 1][1] + abs(B[i] - 1),
                               dp[i - 1][0] + abs(B[i] - B[i - 1]));
        /*consider B[i]!=1, B[i-1]=1 or B[i-1]!=1*/
        printf("%d\n", max(dp[n - 1][0], dp[n - 1][1]));
    }
    return 0;
}
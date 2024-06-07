#include <bits/stdc++.h>
#define int long long
//http://codeforces.com/problemset/problem/1396/C CF1396C Monster Invaders
using namespace std;

constexpr int MAXN = 1e6 + 6;

template<typename T>
void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T>
void Min(T& a, T b) { a = (a < b) ? a : b; }

int tc, n, r1, r2, r3, d, dp[MAXN][2];
array<int, MAXN> a;
//dp[i][0/1] 前 i - 1 层已完成 i层 boss 剩余血量
signed main() {
    read(n), read(r1), read(r2), read(r3), read(d);
    for (int i = 1; i <= n; i++) read(a[i]);
    
    for (int i = 2; i <= n; i++) dp[i][0] = dp[i][1] = 1e18;

    dp[1][0] = 1LL * r1 * a[1] + r3;
    dp[1][1] = min(1LL * r2, 1LL * r1 * a[1] + r1);
    for (int i = 1; i < n; i++) {
        //0->0
        Min(dp[i + 1][0], dp[i][0] + d + 1LL * r1 * a[i + 1] + r3);

        //0->1
        Min(dp[i + 1][1], dp[i][0] + d + min(1LL * r2, 1LL * r1 * a[i + 1] + r1));

        //1->0
        Min(dp[i + 1][0], dp[i][1] + d + 1LL * r1 * a[i + 1] + r3 + 2 * d + r1);
        Min(dp[i + 1][0], dp[i][1] + d + 1LL * r1 * a[i + 1] + r1 + d + r1 + d + r1);
        Min(dp[i + 1][0], dp[i][1] + d + r2 + d + r1 + d + r1);

        //1->1
        Min(dp[i + 1][1], dp[i][1] + d + r2 + d + r1 + d);
        Min(dp[i + 1][1], dp[i][1] + d + 1LL * r1 * a[i + 1] + r1 + d + r1 + d);

        if (i == n - 1) {
            Min(dp[i + 1][0], dp[i][1] + d + 1LL * r1 * a[i + 1] + r3 + d + r1);
        }
    }
    printf("%lld\n", dp[n][0]);
    return 0;
}
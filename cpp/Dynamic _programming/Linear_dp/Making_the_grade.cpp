#include <bits/stdc++.h>
// https://shaun118294191.github.io/post/p2893-usaco08febmaking-the-grade-g/
// P2893 [USACO08FEB]Making the Grade G
#define int long long

constexpr int MAXN = 2e3 + 3;
constexpr int Inf = 2e9;
using namespace std;

template <typename T>
inline void read(T &x) {
    int f = 1;
    x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

unordered_map<int, int> Map;
int n, a[MAXN], cpy[MAXN], cnt, dp[MAXN][MAXN];

inline void discretizaton() {
    sort(cpy + 1, cpy + n + 1);
    cnt = unique(cpy + 1, cpy + n + 1) - cpy - 1;
    for (int i = 1; i <= cnt; i++) Map[cpy[i]] = i;
}

signed main() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]), cpy[i] = a[i];
    discretizaton();
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= cnt; i++) dp[0][i] = 0;
    // for (int i = 1; i <= n; i++)
    // 	for (int j = 1; j <= cnt; j++)
    // 		for (int k = 1; k <= j; k++) {
    // 			dp[i][j] = min(dp[i][j], dp[i - 1][k] + abs(a[i] -
    // cpy[j]));
    // 		}
    for (int i = 1; i <= n; i++) {
        int val = 0x3f3f3f3f3f3f3f3f;
        for (int j = 1; j <= cnt; j++) {
            val = min(val, dp[i - 1][j]);
            dp[i][j] = val + abs(a[i] - cpy[j]);
        }
    }
    cout << *min_element(dp[n] + 1, dp[n] + cnt + 1) << endl;
    return 0;
}
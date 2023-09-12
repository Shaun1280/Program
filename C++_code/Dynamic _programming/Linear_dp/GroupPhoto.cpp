#include <bits/stdc++.h>
// https://codeforces.ml/gym/103186/problem/D
// Zztrans 的班级合照
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

constexpr int MAXN = 5005, MOD = 998244353;

template<typename T>
inline void add(T& a, T b) {
    a += b;
    if (a > MOD) a -= MOD;
}

int n;
int a[MAXN], c[MAXN], sumc[MAXN], f[MAXN];
int dp[MAXN][MAXN]; // dp[i][j] 表示当前升高 <= i，第一排有 j 个同学，且第一排同学个数 >= 第二排
int C[MAXN][MAXN]; // C(n, m) 组合数

signed main() {
    boost;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], c[a[i]]++;
    for (int i = 1; i <= n; i++) sumc[i] = sumc[i - 1] + c[i];
    f[0] = 1;
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % MOD;

    for(int i = 0; i <= n; i++) C[i][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) { // O(n^2)
        int lim = sumc[i];
        for (int j = (lim & 1) ? lim / 2 + 1 : lim / 2; j <= min(n /2, lim); j++) {
            // 枚举当前第一排人数 j，第二排人数为 res
            int res = lim - j;
            for (int k = c[i + 1]; k >= 0; k--) { // 枚举身高为 i + 1 的同学有几个在第一排
                if (j + k < res + (c[i + 1] - k)) break;
                add(dp[i + 1][j + k], dp[i][j] * f[k] % MOD * f[c[i + 1] - k] % MOD * C[c[i + 1]][k] % MOD);
            }
        }
    }
    cout << dp[n][n / 2] << "\n";
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
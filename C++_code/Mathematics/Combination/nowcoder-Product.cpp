#include <bits/stdc++.h>
// https://ac.nowcoder.com/acm/contest/11255/G
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
 
#define int long long
 
constexpr int MAXN = 2505, MOD = 998244353;
 
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
 
int n, k, D;
int frac[MAXN], fracD[MAXN];
int dp[55][MAXN]; // i 个 a 违反限制 (< k)，它们的和为 j 的结果 (含 Π 1/a[i]!)
 
int C(int n, int m) {
    return frac[n] * qpow(frac[m], MOD - 2) % MOD * qpow(frac[n - m], MOD - 2) % MOD;
}
 
signed main() {
    boost;
    cin >> n >> k >> D;
    frac[0] = 1;
    for (int i = 1; i <= n * k; i++) frac[i] = frac[i - 1] * i % MOD;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i * (k - 1); j++) {
            for (int val = 0; val < k; val++) {
                if (j - val >= 0)
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - val] * qpow(frac[val], MOD - 2) % MOD) % MOD;
            }
        }
    }
 
    fracD[0] = 1;
    for (int i = D + 1; i <= D + n * k; i++)
        fracD[i - D] = fracD[i - 1 - D] * i % MOD;
 
    int sum = 0;
    for (int i = 0; i <= n; i++) { // 容斥
        for (int j = 0; j <= i * (k - 1); j++) {
            int sign = (i & 1) ? -1 : 1;
            (sum += sign * dp[i][j] % MOD * C(n, i) % MOD * qpow(n - i, D + n * k - j) % MOD * qpow(fracD[n * k - j], MOD - 2) % MOD) %= MOD;
        }
    }
    cout << ((sum += MOD) %= MOD) << "\n";
    return 0;
}
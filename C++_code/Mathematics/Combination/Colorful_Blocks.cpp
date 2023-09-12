#include <bits/stdc++.h>
//https://atcoder.jp/contests/abc167/tasks/abc167_e
using namespace std;
using LL = long long;

constexpr int MAXN = 2e5 + 5;
constexpr LL Mod = 998244353;

LL n, m, k, ans, fac[MAXN];

inline void Init() {
    fac[0] = 1;
    for (LL i = 1; i < MAXN; i++) fac[i] = fac[i - 1] * i % Mod;
}

inline LL qpow(LL a, LL b) {// a^b
    LL res = 1;
    while (b) {
        if (b & 1) res = res * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return res;
}

inline LL C(LL N, LL M) {
    if (M > N || M < 0) return 0;
    return fac[N] * qpow(fac[M], Mod - 2) % Mod * qpow(fac[N - M], Mod - 2) % Mod;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    Init();
    for (LL i = 0 ; i <= k; i++)
        ans = (ans + C(n - 1, i) * m % Mod * qpow(m - 1, n - i - 1) % Mod) % Mod;
    cout << ans << endl;
    return 0;
}

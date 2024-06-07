#include <bits/stdc++.h>
// Connectivity 2
// https://atcoder.jp/contests/abc213/tasks/abc213_g
// 删除若干边，求 1 与 k 连通的图的个数
// g[s] 表示点集 s 能够构成的子图数目
// f[s] 表示点集 s 联通子图数目
// g[s]: 求出 s 中边(连接 s 中两点)的数量 e，g[s] = 2^e O(M2^n)
// f[s] = g[s] - Σf[t]*g[s-t], t 真包含于 s
// 注意 g 包含了 f，为避免算重，要求枚举的点集 ts 必须包含同一点，用最低位 1 对应的点。
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

constexpr int MOD = 998244353;

int n, m;
int a[17 * 17], b[17 * 17];
int f[1 << 17], g[1 << 17];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

signed main() {
    boost;
    cin >> n >> m;
    int V = (1 << n) - 1;
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i], a[i]--, b[i]--;
    for (int i = 0; i <= V; i++) {
        int cnt(0);
        for (int j = 1; j <= m; j++) {
            if ((i & (1 << a[j])) && (i & (1 << b[j]))) cnt++;
        }
        g[i] = qpow(2LL, cnt); // get g[i]

        if (i == 0) continue;

        f[i] = g[i];
        int ct = __builtin_ctz(i); // 尾数 0 的个数 i = 0 -> undefined
        for (int j = i - 1; j >= 0; j--) {
            j &= i;
            if ((j >> ct) & 1) {
                f[i] -= f[j] * (g[i - j]) % MOD;
                (f[i] += MOD) %= MOD;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        int ans(0);
        for (int st = 0; st <= V; st++) {
            if ((st & (1 << i)) && (st & 1)) ans = (ans + f[st] * g[V - st] % MOD) % MOD;
        }
        cout << ans << "\n";
    }
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
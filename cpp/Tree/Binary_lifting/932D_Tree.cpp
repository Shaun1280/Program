#include <bits/stdc++.h>
#define int long long
//https://codeforces.ml/contest/932/problem/D
using namespace std;

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 4e5 + 5, MOD = 1e9 + 7, INF = 1e16, LIM = 19;

int q, last, type, u, x, cur, dp[MAXN][LIM + 1], sum[MAXN][LIM + 1], w[MAXN];
//dp[u][i] u 向上经过 2^i 个权值大于等与 w[u] 的节点后的位置 不包括自身
inline void init() {
    cur = 1, w[cur] = 0, w[0] = INF;
    for (int i = 0; i <= LIM; i++) sum[1][i] = INF;
}
//sum[u][i] u 向上经过 2^i 个权值大于等与 w[u] 的节点后的和(只统计这 2^i 个数)
inline void add() {
    w[++cur] = x;
    if (w[cur] <= w[u]) dp[cur][0] = u;
    else {
        for (int i = LIM; i >= 0; i--)
            if (w[cur] > w[dp[u][i]]) u = dp[u][i];
        dp[cur][0] = dp[u][0]; //类似lca 需要找到dp[u][0]
    }

    if (dp[cur][0] == 0) sum[cur][0] = INF;
    else sum[cur][0] = w[dp[cur][0]];

    for (int i = 1; i <= LIM; i++) {
        dp[cur][i] = dp[dp[cur][i - 1]][i - 1];
        if (dp[cur][i] == 0) sum[cur][i] = INF;
        else sum[cur][i] = sum[cur][i - 1] + sum[dp[cur][i - 1]][i - 1];
    }
}

inline int query(int res = 1) {
    if (w[u] > x) return 0;
    x -= w[u];
    for (int i = LIM; i >= 0; i--) {
        if (x >= sum[u][i]) {
            x -= sum[u][i];
            res += (1 << i);
            u = dp[u][i];
        }
    }
    return res;
}

signed main() {
    read(q);
    init();
    while (q--) {
        read(type, u, x);
        u ^= last, x ^= last;
        if (type == 1) add();
        else printf("%lld\n", last = query());
    }
    return 0;
}
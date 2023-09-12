#include <bits/stdc++.h>
// https://codeforces.com/blog/entry/73934
/*
Assume that the length of a path from a to b is L.

It is obvious that for every non-negative integer Z, there exists a path from a
to b of length L+2Z since we can go back and forth any edge along the path any
number of times.

So, we want to find the shortest path from a to b where the parity (odd or even)
of its length is same as the parity of k.

Since it is a tree, the parity of the length of every paths from a to b is
unique.

However, if we add another edge, we can possibly find a path of length with
different parity.

The parity is changed only if you use the added edge odd number of times and the
length of the simple path from x to y is even.

Since there is no reason to take the path multiple times to find
the shortest path of same parity, let's assume we use it only once.

If it doesn't change the parity, we can think of it as trying to find a shorter
path with same parity of length.

Then there are three paths we need to check:

The simple path from a to b without using the added edge.
The simple path from a to x without using the added edge, plus the added edge,
plus the simple path from y to b without using the added edge. The simple path
from a to y without using the added edge, plus the added edge, plus the simple
path from x to b without using the added edge.
*/
constexpr int MAXN = 1e5 + 5;
constexpr int LIM = 18;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
int testCase, n, tot, f[MAXN][20];
array<int, MAXN> depth;
vector<pair<double, pair<int, int>>> vec;
vector<vector<int>> G;
inline void dfs(int cur, int fa) {
    depth[cur] = depth[fa] + 1;
    f[cur][0] = fa;
    for (int i = 1; i < LIM; i++) f[cur][i] = f[f[cur][i - 1]][i - 1];
    for (auto to : G[cur]) {
        if (to != fa) dfs(to, cur);
    }
}
inline int LCA(int u, int v) {  // LCA模板 返回u, v间的最大边长
    int x = u, y = v;
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LIM - 1; i >= 0; i--)  //枚举i级祖先
        if (depth[f[u][i]] >= depth[v]) {
            u = f[u][i];  // u向上跳
        }
    if (u == v) return depth[x] + depth[y] - 2 * depth[u];
    for (int i = LIM - 1; i >= 0; i--)  //枚举i级祖先
        if (f[u][i] != f[v][i]) {
            u = f[u][i], v = f[v][i];  // u, v向上跳 直至找到公共祖先前一个位置
        }
    return depth[x] + depth[y] - 2 * depth[f[u][0]];
}
int main() {
    n = read();
    G.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int u = read(), v = read();
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 0);
    int Q = read();
    while (Q--) {
        int x = read(), y = read(), a = read(), b = read(), k = read(),
            ans = 0x3f3f3f3f;
        int without = LCA(a, b);
        int with = min(LCA(a, x) + LCA(y, b), LCA(a, y) + LCA(x, b)) + 1;
        if (without % 2 == k % 2) ans = without;
        if (with % 2 == k % 2) ans = min(ans, with);
        ans <= k ? puts("YES") : puts("NO");
    }
    return 0;
}
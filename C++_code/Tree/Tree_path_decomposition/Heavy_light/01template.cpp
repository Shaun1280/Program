#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P3384 P3384 【模板】轻重链剖分
using namespace std;
using LL = long long;

constexpr int MAXN = 1e5 + 5, MOD = 998244353;

int n, m, r, p;
array<int, MAXN> val, hSon, top, rnk, fa, depth, sz, in;
vector<int> G[MAXN];

struct BIT {
    int lowbit(int x) { return x & (~x + 1); }

    void build (int x = 2, int sub = 1) {
        while (x <= n) {
            for (int i = x; i <= n; i += x)
                (c[i] += c[i - sub]) %= p;
            x <<= 1, sub <<= 1;
        }
    }

    void add(int x, LL val) {
        while (x <= n) (c[x] += val) %= p, x += lowbit(x);
    }

    LL query(int x, LL res = 0) {
        while (x) (res += c[x]) %= p, x -= lowbit(x);
        return res;
    }
    array<LL, MAXN> c;
} bit[3];
/*range [l, r] add val*/
inline void add(int l, int r, LL val) {
    bit[1].add(l, val), bit[1].add(r + 1, -val);
    bit[2].add(l, val * l), bit[2].add(r + 1, -val * (r + 1));
}
/*range [l, r] sum query*/
inline int query(int l, int r, LL res = 0) {
    (res = bit[0].query(r) + bit[1].query(r) * (r + 1) - bit[2].query(r)) %= p;
    (res -= bit[0].query(l - 1) + bit[1].query(l - 1) * l - bit[2].query(l - 1)) % p;
    return (res + p) % p;
}

void dfs1(int cur, int f) {
    sz[cur] = 1, fa[cur] = f, depth[cur] = depth[f] + 1;
    for (auto& to : G[cur]) {
        if (to == f) continue;
        dfs1(to, cur);
        sz[cur] += sz[to];
        if (!hSon[cur] || sz[to] > sz[hSon[cur]]) hSon[cur] = to;
    }
}

void dfs2(int cur, int f) {
    static int tim;
    in[cur] = ++tim, top[cur] = f, rnk[tim] = cur;
    if (!hSon[cur]) return;
    dfs2(hSon[cur], f); //优先重链
    for (auto& to : G[cur]) {
        if (to != hSon[cur] && to != fa[cur]) dfs2(to, to);
    }
}

inline void chainAdd(int u, int v, int z) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        add(in[top[u]], in[u], z);
        u = fa[top[u]];
    }
    if (in[u] > in[v]) swap(u, v);
    add(in[u], in[v], z);
}

inline int chainQuery(int u, int v, int res = 0) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        (res += query(in[top[u]], in[u])) %= p;
        u = fa[top[u]];
    }
    if (in[u] > in[v]) swap(u, v);
    (res += query(in[u], in[v])) %= p;
    return (res + p) % p;
}

inline void treeAdd(int u, int z) { add(in[u], in[u] + sz[u] - 1, z); }

inline int treeQuery(int u) { return (query(in[u], in[u] + sz[u] - 1) % p + p) % p; }

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m >> r >> p;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs1(r, r), dfs2(r, r);
    for (int i = 1; i <= n; i++) bit[0].c[i] = val[rnk[i]] % p;
    bit[0].build();
    int opt, x, y, z;
    while (m--) {
        cin >> opt;
        switch (opt) {
            case 1: cin >> x >> y >> z; chainAdd(x, y, z); break;
            case 2: cin >> x >> y; cout << chainQuery(x, y) << "\n"; break;
            case 3: cin >> x >> z; treeAdd(x, z); break;
            case 4: cin >> x; cout << treeQuery(x) << "\n"; break;
        }
    }
    return 0;
}
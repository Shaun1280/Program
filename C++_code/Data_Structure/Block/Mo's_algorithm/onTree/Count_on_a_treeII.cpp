#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/SP10707
using namespace std;
// u 到 v 的 路径上不同颜色数目 欧拉序 + 莫队
constexpr int MAXN = 1e5 + 5;

template<typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? - 1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int n, q, base, tmp;
vector<int> G[MAXN];
array<int, MAXN> col, cnt, in, out, hSon, top, sz, depth, fa, from;
array<int, MAXN> belong, vis, ans;

struct Query {
    int l, r, id, lca;
    friend inline bool operator<(const Query& lhs, const Query& rhs) {
        if (belong[lhs.l] == belong[rhs.l]) return lhs.r < rhs.r;
        return lhs.l < rhs.l;
    }
} Q[MAXN];

void dfs1(int cur, int f) {
    static int tim;
    in[cur] = ++tim, from[tim] = cur;
    sz[cur] = 1, fa[cur] = f, depth[cur] = depth[f] + 1;
    for (auto& to : G[cur]) {
        if (to == fa[cur]) continue;
        dfs1(to, cur);
        sz[cur] += sz[to];
        if (!hSon[cur] || sz[to] > sz[hSon[cur]]) hSon[cur] = to;
    }
    out[cur] = ++tim, from[tim] = cur;
}

void dfs2(int cur, int f) {
    top[cur] = f;
    if (!hSon[cur]) return;
    dfs2(hSon[cur], f); //优先重链
    for (auto& to : G[cur]) {
        if (to != hSon[cur] && to != fa[cur]) dfs2(to, to);
    }
}

inline int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return depth[u] < depth[v] ? u : v;
}

inline void calc(int x) { //x 为 欧拉序 from[x] 当前欧拉序对应节点编号
    int color = col[from[x]];
    int delta = vis[from[x]] ? - 1 : 1;
    cnt[color] += delta;
    if (delta == -1 && !cnt[color]) tmp--;
    if (delta == 1 && cnt[color] == 1) tmp++;
    vis[from[x]] ^= 1;
}

unordered_map<int, int> mp;
inline void discrete() {
    vector<int> vec;
    for (int i = 1; i <= n; i++) vec.push_back(col[i]);
    sort(vec.begin(), vec.end());
    int cnt = unique(vec.begin(), vec.end()) - vec.begin();
    for (int i = 0; i < cnt; i++) mp[vec[i]] = i + 1;
    for (int i = 1; i <= n; i++) col[i] = mp[col[i]];
}

int main () {
    read(n), read(q), base = pow(2 * n, 0.54);
    for (int i = 1; i <= n; i++) read(col[i]);
    discrete();
    for (int i = 1; i <= 2 * n; i++) belong[i] = i / base;
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs1(1, 1), dfs2(1, 1);
    for (int i = 1, u, v; i <= q; i++) {
        read(u), read(v);
        if (in[u] > in[v]) swap(u, v);
        Q[i].id = i, Q[i].lca = LCA(u, v);
        if (Q[i].lca == u)
            Q[i].l = in[u], Q[i].r = in[v], Q[i].lca = 0;
        else Q[i].l = out[u], Q[i].r = in[v];
    }
    sort(Q + 1, Q + q + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= q; i++) {
        while (r < Q[i].r) calc(++r);
        while (r > Q[i].r) calc(r--);
        while (l < Q[i].l) calc(l++);
        while (l > Q[i].l) calc(--l);
        if (Q[i].lca) calc(in[Q[i].lca]);
        ans[Q[i].id] = tmp;
        if (Q[i].lca) calc(in[Q[i].lca]);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}
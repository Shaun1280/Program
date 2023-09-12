#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P4074 [WC2013]糖果公园
using namespace std;
//树上带修莫队
constexpr int MAXN = 2e5 + 5;

template <typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int n, m, q, base, cntQ, cntR;
long long tmp, ans[MAXN];
vector<int> G[MAXN];
array<int, MAXN> v, w;  //美味指数 新奇度
array<int, MAXN> col, cnt, in, out, hSon, top, sz, depth, fa, from;
array<int, MAXN> belong, vis;

struct Query {
    int l, r, id, lca, tim;
    friend inline bool operator<(const Query& lhs, const Query& rhs) {
        if (belong[lhs.l] != belong[rhs.l]) return lhs.l < rhs.l;
        if (belong[lhs.r] != belong[rhs.r]) return lhs.r < rhs.r;
        return lhs.tim < rhs.tim;
    }  //不同块按左端点排序，左端点所在块相同按右端点所在块排序，相同块则按时间排序
} Q[MAXN];

struct Change {
    int node, col;
} chg[MAXN];

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
    dfs2(hSon[cur], f);  //优先重链
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

inline void calc(int x) {  // x 为 欧拉序 from[x] 当前欧拉序对应节点编号
    int color = col[from[x]];
    if (!vis[from[x]]) { //该节点没有被访问
        ++cnt[color]; //当前颜色计数加 1
        tmp += 1LL * w[cnt[color]] * v[color];
    } else {
        tmp -= 1LL * w[cnt[color]] * v[color];
        --cnt[color];
    }
    vis[from[x]] ^= 1;
}

inline void change(Change& change) {
    if (vis[change.node]) {
        calc(in[change.node]); //先删除
        swap(change.col, col[change.node]);
        calc(in[change.node]);
    } else swap(change.col, col[change.node]);
}

int main() {
    read(n), read(m), read(q), base = pow(2 * n, 0.66);
    for (int i = 1; i <= m; i++) read(v[i]);
    for (int i = 1; i <= n; i++) read(w[i]);
    for (int i = 1; i <= 2 * n; i++) belong[i] = i / base;
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        G[u].push_back(v), G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) read(col[i]);
    dfs1(1, 1), dfs2(1, 1);

    for (int i = 1, opt, u, v; i <= q; i++) {
        read(opt), read(u), read(v);
        if (opt == 1) {  //询问
            cntQ++;
            if (in[u] > in[v]) swap(u, v);
            Q[cntQ].id = cntQ, Q[cntQ].tim = cntR; //▲
            Q[cntQ].lca = LCA(u, v);
            if (Q[cntQ].lca == u)
                Q[cntQ].l = in[u], Q[cntQ].r = in[v], Q[cntQ].lca = 0;
            else Q[cntQ].l = out[u], Q[cntQ].r = in[v];
        } else cntR++, chg[cntR].node = u, chg[cntR].col = v; //修改
    }

    sort(Q + 1, Q + cntQ + 1);
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= cntQ; i++) {
        while (r < Q[i].r) calc(++r);
        while (r > Q[i].r) calc(r--);
        while (l < Q[i].l) calc(l++);
        while (l > Q[i].l) calc(--l);
        while (t < Q[i].tim) change(chg[++t]);
        while (t > Q[i].tim) change(chg[t--]);
        if (Q[i].lca) calc(in[Q[i].lca]);
        ans[Q[i].id] = tmp;
        if (Q[i].lca) calc(in[Q[i].lca]);
    }
    for (int i = 1; i <= cntQ; i++) printf("%lld\n", ans[i]);
    return 0;
}
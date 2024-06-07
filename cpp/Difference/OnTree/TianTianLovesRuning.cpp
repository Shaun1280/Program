#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/P1600
//https://shaun118294191.github.io/post/tian-tian-ai-pao-bu/
constexpr int MAXN = 3e5 + 5;
constexpr int ADD = 3e5;
constexpr int LOG = 20;

using namespace std;
using A = int [MAXN << 1];

template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int n, m, f[MAXN][LOG];
A res, depth, w, cnt1, cnt2, s, t;
vector<int> G[MAXN];
vector< pair<int, int> > vec1[MAXN], vec2[MAXN];

inline void dfs(int cur, int fa) {
    f[cur][0] = fa, depth[cur] = depth[fa] + 1;
    for (int i = 1; i < LOG; i++)
        f[cur][i] = f[f[cur][i - 1]][i - 1];
    for (auto &to : G[cur]) {
        if (to == fa) continue;
        dfs(to, cur);
    }
}

inline int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--)
        if (depth[f[u][i]] >= depth[v])
            u = f[u][i];
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--)
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}

inline void getRes(int cur, int fa) {
    int pre = cnt1[w[cur] + depth[cur] + ADD] + cnt2[w[cur] - depth[cur] + ADD]; 
    //其它子树中的cntDis需减去
    for (auto &to : G[cur]) {
        if (to == fa) continue;
        getRes(to, cur);
    }
    for (auto &i : vec1[cur]) cnt1[i.first + ADD] += i.second; //两类cnt
    for (auto &i : vec2[cur]) cnt2[i.first + ADD] += i.second; 
    res[cur] += cnt1[w[cur] + depth[cur] + ADD] + cnt2[w[cur] - depth[cur] + ADD] - pre;
}

int main() {
    read(n), read(m);
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) read(w[i]);
    for (int i = 1; i <= m; i++) {
        read(s[i]), read(t[i]);
        int lca = LCA(s[i], t[i]);
        vec1[s[i]].emplace_back(make_pair(depth[s[i]], 1));
        vec1[f[lca][0]].emplace_back(make_pair(depth[s[i]], -1));
        vec2[t[i]].emplace_back(make_pair(depth[s[i]] - 2 * depth[lca], 1));
        vec2[lca].emplace_back(make_pair(depth[s[i]] - 2 * depth[lca], -1));
    }
    getRes(1, 0);
    for (int i = 1; i <= n; i++) printf("%d ", res[i]);
    return 0;
}
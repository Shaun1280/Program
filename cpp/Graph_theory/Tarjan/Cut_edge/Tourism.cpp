#include <bits/stdc++.h>
#define int long long
//https://codeforces.ml/contest/1220/problem/E  
using namespace std;
//Codeforces Round #586 (Div. 1 + Div. 2)
constexpr int MAXN = 4e5 + 5; //注意双向边
 
template <typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
 
struct Edge {
    Edge() = default;
    Edge(int _to, int _next) : to(_to), next(_next) {}
    int to, next;
};
vector<Edge> edge;
array<int, MAXN> dfn, low, head, bridge;
array<int, MAXN> w, belong, sum, sz;
int n, tot, u, v, m, s, edcc;
 
inline void addEdge(int from, int to) {
    edge.emplace_back(to, head[from]), head[from] = edge.size() - 1;
    edge.emplace_back(from, head[to]), head[to] = edge.size() - 1;
}
 
void tarjan(int cur, int in_edge) {  // tarjan求割边
    dfn[cur] = low[cur] = ++tot;
    for (int i = head[cur]; ~i; i = edge[i].next) {
        int to = edge[i].to;
        if (!dfn[to]) {  //在搜索树上
            tarjan(to, i);
            low[cur] = min(low[cur], low[to]);
            if (dfn[cur] < low[to])  //割边判定条件
                bridge[i] = bridge[i ^ 1] = true;
        } else if (i != (in_edge ^ 1))  //不是入边且不在搜索树上
            low[cur] = min(low[cur], dfn[to]);
    }
}
 
void dfs(int cur) {
    belong[cur] = edcc, sum[edcc] += w[cur], sz[edcc]++;
    for (int i = head[cur]; ~i; i = edge[i].next) {
        int to = edge[i].to;
        if (belong[to] || bridge[i]) continue;
        dfs(to);
    }
}
 
vector<int> G[MAXN], vec;
array<int, MAXN> ret, f, g; //f[cur] 走到 cur子树并返回 g[cur] 不返回
 
inline void DP(int cur, int fa) {
    f[cur] = sum[cur];
    if (sz[cur] > 1) ret[cur] = 1;
    int mx = 0;
    for (auto& to : G[cur]) {
        if (to == fa) continue;
        DP(to, cur);
        if (ret[to]) f[cur] += f[to], ret[cur] = 1;
        else mx = max(mx, g[to]);
    }
    g[cur] = f[cur] + mx;
    for (auto& to : G[cur]) {
        if (to == fa || !ret[to]) continue;
        g[cur] = max(g[cur], f[cur] + g[to] - f[to]); //cur 不返回
    }
}
 
signed main() {
    fill(head.begin(), head.end(), -1);
    read(n), read(m);
    for (int i = 0; i < n; i++) read(w[i]);
    for (int i = 0; i < m; i++) {
        read(u), read(v);
        u--, v--;
        addEdge(u, v);
    }
    read(s), s--;
    for (int i = 0; i < n; i++) if (!dfn[i]) tarjan(i, -1);
    for (int i = 0; i < n; i++) if (!belong[i]) ++edcc, dfs(i);
    for (int i = 0; i < edge.size(); i += 2) {
        u = belong[edge[i].to], v = belong[edge[i ^ 1].to];
        if (u != v) G[u].push_back(v), G[v].push_back(u);
    }
    DP(belong[s], 0);
    cout << g[belong[s]] << "\n";
    return 0;
}
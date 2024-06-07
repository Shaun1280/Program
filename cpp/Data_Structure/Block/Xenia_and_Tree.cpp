#include <bits/stdc++.h>
// 把红色节点按照 S 分块
// 新加入的红色节点达到 S 个时，bfs 更新
// 否则暴力求 lca
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

int n, m, B;
vector<int> g[MAXN];
vector<int> red;

int sz[MAXN], fa[MAXN], hson[MAXN], in[MAXN], top[MAXN], depth[MAXN];
void dfs1(int cur, int f) {
    sz[cur] = 1, fa[cur] = f, depth[cur] = depth[f] + 1;
    for (auto& to : g[cur]) {
        if (to == f) continue;
        dfs1(to, cur);
        sz[cur] += sz[to];
        if (!hson[cur] || sz[to] > sz[hson[cur]]) hson[cur] = to;
    }
}

void dfs2(int cur, int f) {
    static int tim;
    in[cur] = ++tim, top[cur] = f;
    if (!hson[cur]) return;
    dfs2(hson[cur], f);
    for (auto& to : g[cur]) {
        if (to == hson[cur] || to == fa[cur]) continue;
        dfs2(to, to);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return in[u] < in[v] ? u : v;
}

int dis[MAXN], vis[MAXN];
void bfs() {
    queue<int> q;
    for (int i = 1; i <= n; i++) vis[i] = false;
    for (auto& v : red) dis[v] = 0, q.push(v), vis[v] = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto& to : g[cur]) {
            if (!vis[to]) {
                q.push(to);
                vis[to] = true;
                dis[to] = min(dis[to], dis[cur] + 1);
            }
        }
    }
}

int main() {
    boost;
    cin >> n >> m;
    B = sqrt(n) + 1;
    memset(dis, 0x3f, sizeof(dis));
    red.push_back(1);
    bfs();
    for (int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b), g[b].push_back(a);
    }
    dfs1(1, 0), dfs2(1, 1);
    for (int i = 1; i <= m; i++) {
        int op, u;
        cin >> op >> u;
        if (op == 1) {
            red.push_back(u);
            if (red.size() == B) {
                bfs();
                red.clear();
            }
        } else {
            int res = dis[u];
            for (auto& v : red) res = min(res, depth[u] + depth[v] - 2 * depth[lca(u, v)]);
            cout << res << "\n";
        }
    }
    return 0;
}
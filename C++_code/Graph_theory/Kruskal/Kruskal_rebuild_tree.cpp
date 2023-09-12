#include <bits/stdc++.h>
// icpc shanghai 2021 H
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7, LIM = 18;

int n, m, q;
int fa[MAXN], f[MAXN][LIM + 1];
long long g[MAXN][LIM + 1];
long long sum[MAXN], val[MAXN];
vector<int> G[MAXN];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
} e[MAXN];

void dfs(int cur, int fa) {
    if (G[cur].size() == 0) sum[cur] = val[cur];
    for (auto& to : G[cur]) {
        dfs(to, cur);
        sum[cur] += sum[to];
    }
}

void dfs2(int cur, int fa) {
    g[cur][0] = val[fa] - sum[cur], f[cur][0] = fa;
    for (int i = 1; i <= LIM; i++) {
        f[cur][i] = f[f[cur][i - 1]][i - 1];
        g[cur][i] = max(g[cur][i - 1], g[f[cur][i - 1]][i - 1]);
    }
    for (auto& to : G[cur]) dfs2(to, cur);
}

void query(int x, int k) {
    for (int i = LIM; i >= 0; i--) {
        if (f[x][i] && g[x][i] <= k) x = f[x][i];
    }
    cout << sum[x] + k << "\n";
}

int main() {
    boost;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i <= 2 * n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e + 1, e + m + 1);
    int cnt(n);
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int r1 = find(u), r2 = find(v);
        if (r1 != r2) {
            fa[r1] = ++cnt, fa[r2] = cnt;
            val[cnt] = w;
            G[cnt].push_back(r1), G[cnt].push_back(r2);
        }
    }
    dfs(cnt, 0);
    dfs2(cnt, 0);
    for (int i = 1, x, k; i <= q; i++) {
        cin >> x >> k;
        query(x, k);
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
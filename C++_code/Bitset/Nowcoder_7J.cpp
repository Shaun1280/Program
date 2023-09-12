#include <bits/stdc++.h>
// https://ac.nowcoder.com/acm/contest/11258/J 牛客多校第 7 场 xay loves Floyd
using namespace std;
// 本身就有一条边 (x, y, w) dis[x][y] = w, 则 dis[x][y] 正确
// 存在一个点 z，满足 dis[x][z], dis[z][y] 的值均正确，且 z 位于 x 到 y 的某一条最短路上
// 用 can[u][v] 记录 dis[u][v] 的正确性 can[u][v] = can[u][*] & can[*][v] & pot[v]
// pot[v] 为 u 到 v 所有最短路经过点的集和，bitset 优化复杂度
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2002, MOD = 1e9 + 7;

int n, m, dis[MAXN][MAXN], vis[MAXN][MAXN], ans;
int e[MAXN][MAXN], perm[MAXN];
bitset<2001> f[MAXN], g[MAXN], pot[MAXN];
vector<pair<int, int>> G[MAXN];

void dijkstra(int x) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.emplace(dis[x][x] = 0, x);
    while (!q.empty()) {
        int dist, cur;
        tie(dist, cur) = q.top();
        q.pop();
        if (vis[x][cur]) continue;
        for (auto& e : G[cur]) {
            int to = e.first, w = e.second;
            if (dis[x][to] > dist + w) {
                dis[x][to] = dist + w;
                q.emplace(dis[x][to], to);
            }
        }
        vis[x][cur] = true;
    }
}

int main() {
    boost;
    cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));
    memset(e, 0x3f, sizeof(e));
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        e[u][v] = w;
    }
    for (int i = 1; i <= n; i++) {
        perm[i] = i;
        e[i][i] = 0;
        dijkstra(i);
        for (int j = 1; j <= n; j++)
            if (e[i][j] == dis[i][j]) f[i].set(j), g[j].set(i);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) pot[j].reset();
        for (int j = 1; j <= n; j++) pot[j].set(j);
        sort(perm + 1, perm + n + 1, [&](const int& a, const int& b){
            return dis[i][a] < dis[i][b];
        });
        for (int j = 1; j <= n; j++) {
            int cur = perm[j];
            for (auto& e : G[cur]) {
                int to = e.first, w = e.second;
                if (dis[i][cur] + w == dis[i][to]) pot[to] |= pot[cur];
            }
        }
        for (int j = 1; j <= n; j++) {
            if (((f[i] & g[j]) & pot[j]).count()) {
                f[i].set(j), g[j].set(i);
            }
        }
    }
    for (int i = 1; i <= n; i++) ans += f[i].count();
    cout << ans << "\n";
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
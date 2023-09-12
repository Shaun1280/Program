#include <bits/stdc++.h>
// https://atcoder.jp/contests/abc212/tasks/abc212_f
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7, LOG = 20;

int n, m, q, fa[MAXN][LOG];
long long dis[MAXN][LOG];
struct Bus {
    int a, b, s, t, id;
    bool operator<(const Bus& other) const {
        return s < other.s;
    }
} bus[MAXN];
vector<Bus> city[MAXN]; // 每个城市出发的车 按 s 排序

vector<int> g[MAXN];
void dfs(int cur, int f) {
    fa[cur][0] = f;
    for (int i = 1; i < LOG; i++)
        fa[cur][i] = fa[fa[cur][i - 1]][i - 1];
    for (auto& to : g[cur]) {
        if (to == f) continue;
        dfs(to, cur);
    }
}

void solve(int x, int y, int z) {
    bus[0].s = x;
    int pos = lower_bound(city[y].begin(), city[y].end(), bus[0]) - city[y].begin();
    if (pos < city[y].size()) {
        int cur = city[y][pos].id;
        for (int i = LOG - 1; i >= 0; i--) // binary lifting
            if (fa[cur][i] && bus[fa[cur][i]].t < z)
                cur = fa[cur][i];
        if (bus[cur].s >= z) cout << y << "\n";
        else if (bus[cur].t >= z) cout << bus[cur].a << " " << bus[cur].b << "\n";
        else if (!fa[cur][0]) cout << bus[cur].b << "\n";
        else if (bus[fa[cur][0]].s >= z) cout << bus[cur].b << "\n";
        else cout << bus[fa[cur][0]].a << " " << bus[fa[cur][0]].b << "\n";
    } else cout << y << "\n";
}

int main() {
    boost;
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        cin >> bus[i].a >> bus[i].b >> bus[i].s >> bus[i].t;
        bus[i].id = i, city[bus[i].a].push_back(bus[i]); // 按 bus 建图 起点/终点相同且满足条件则连边
    }
    for (int i = 1; i <= n; i++) sort(city[i].begin(), city[i].end());
    for (int i = 1; i <= m; i++) {
        bus[0].s = bus[i].t;
        int to = bus[i].b;
        int pos = lower_bound(city[to].begin(), city[to].end(), bus[0]) - city[to].begin();
        if (pos < city[to].size()) g[city[to][pos].id].push_back(bus[i].id);
    }
    for (int i = 1; i <= m; i++) if (fa[i][0] == 0) dfs(i, 0);
    for (int i = 1, x, y, z; i <= q; i++) {
        cin >> x >> y >> z;
        solve(x, y, z);
    }
    return 0;
}
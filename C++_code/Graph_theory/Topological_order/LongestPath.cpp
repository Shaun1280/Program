#include <bits/stdc++.h>
// DAG longest path from 1 to n
constexpr int MAXN = 2e3 + 3;
constexpr int negaInf = 0xcfcfcfcf;

using namespace std;

int n, m, in[MAXN], dis[MAXN], maxDis;

vector<vector<pair<int, int>>> G;

inline void topoSort() {
    queue<int> q;
    dis[1] = 0;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0 && G[i].size()) q.push(i);
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto i : G[cur]) {
            int to = i.first, w = i.second;
            dis[to] = max(dis[to], dis[cur] + w);
            if (!(--in[to])) q.push(to);
        }
    }
    cout << (dis[n] == negaInf ? -1 : dis[n]);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    G.resize(n + 1);
    memset(dis, 0xcf, sizeof(dis));
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back(make_pair(v, w));
        in[v]++;
    }
    topoSort();
    return 0;
}
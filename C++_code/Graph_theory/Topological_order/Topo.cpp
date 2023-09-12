#include <bits/stdc++.h>

constexpr int MAXN = 1e4 + 4;

using namespace std;

int in[MAXN], n, m, fa[MAXN];
vector<vector<int>> E;

inline void topoOrder() {
    queue<int> q;
    vector<int> topo;
    for (int i = 1; i <= n; i++)
        if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        topo.push_back(cur);
        for (auto to : E[cur])
            if (!(--in[to])) q.push(to);
    }
    cout << topo.size() << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    E.resize(n + 1);
    for (int i = 0; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        E[u].push_back(v);
        in[v]++;
    }
    topoOrder();
    return 0;
}
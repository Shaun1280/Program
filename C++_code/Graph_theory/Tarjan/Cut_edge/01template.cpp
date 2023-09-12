#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/UVA796 UVA796 Critical Links
using namespace std;

constexpr int MAXN = 1e5 + 5;

template<typename T>
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
vector<pair<int, int>> vecBridge;
map<pair<int, int>, bool> connected;
int n, cntBridge, tot, u, v, m;

inline void addEdge(int from, int to) {
    edge.emplace_back(to, head[from]), head[from] = edge.size() - 1;
    edge.emplace_back(from, head[to]), head[to] = edge.size() - 1;
}

void tarjan(int cur, int in_edge) { //tarjan求割边
    dfn[cur] = low[cur] = ++tot;
    for (int i = head[cur]; ~i; i = edge[i].next) {
        int to = edge[i].to;
        if (!dfn[to]) { //在搜索树上
            tarjan(to, i);
            low[cur] = min(low[cur], low[to]);
            if (dfn[cur] < low[to]) //割边判定条件
                bridge[i] = bridge[i ^ 1] = true;
        } else if (i != (in_edge ^ 1)) //不是入边且不在搜索树上
            low[cur] = min(low[cur], dfn[to]);
    }
}

int main() {
    while (cin >> n) {
        edge.clear(), vecBridge.clear(), connected.clear();
        fill(head.begin(), head.end(), -1), fill(bridge.begin(), bridge.end(), 0);
        fill(dfn.begin(), dfn.end(), 0), fill(low.begin(), low.end(), 0);
        cntBridge = 0, tot = 0;
        for (int i = 0; i < n; i++) {
            read(u), read(m);
            for (int j = 0; j < m; j++) {
                read(v);
                if (!connected[make_pair(u, v)]) { //防止重复建边
                    connected[make_pair(u, v)] = true;
                    connected[make_pair(v, u)] = true;
                    addEdge(u, v);
                }
            }
        }
        for (int i = 0; i < n; i++) if (!dfn[i]) tarjan(i, -1);
        for (int i = 0; i < edge.size(); i += 2) {
            if (!bridge[i]) continue;
            cntBridge++;
            u = edge[i].to, v = edge[i ^ 1].to;
            vecBridge.push_back(make_pair(min(u, v), max(u, v)));
        }
        printf("%d critical links\n", cntBridge);
        sort(vecBridge.begin(), vecBridge.end());
        for (auto& i : vecBridge) printf("%d - %d\n", i.first, i.second);
        printf("\n");
    }
}
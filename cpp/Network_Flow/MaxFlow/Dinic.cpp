#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P2740 P2740 [USACO4.2]草地排水Drainage Ditches
using namespace std;

constexpr int MAXN = 1e3;
constexpr int INF = 0x3f3f3f3f;

struct Edge {
    Edge() = default;
    Edge(int _to, int _c, int _next) : to(_to), c(_c), next(_next) {}
    /*@param c capacity*/
    int to, c, next;
};
vector<Edge> edge;
int n, m, s, t, maxFlow;
array<int, MAXN> head, curv, depth;

inline void addEdge(int from, int to, int c) {
    edge.emplace_back(to, c, head[from]), head[from] = edge.size() - 1;
    edge.emplace_back(from, 0, head[to]), head[to] = edge.size() - 1;
}

inline bool bfs() {
    fill(depth.begin(), depth.end(), 0);
    copy(head.begin(), head.end(), curv.begin());
    queue<int> q;
    q.push(s), depth[s] = 1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = head[cur]; ~i; i = edge[i].next) {
            int to = edge[i].to;
            if (!edge[i].c || depth[to]) continue;
            depth[to] = depth[cur] + 1;
            q.push(to);
            if (to == t) return true;
        }
    }
    return false;
}

int dfs(int cur, int limit) {
    if (!limit || cur == t) return limit;
    int flow(0);
    for (int i = curv[cur]; ~i; i = edge[i].next) {
        curv[cur] = i;
        int to = edge[i].to;
        if (edge[i].c && depth[to] == depth[cur] + 1) {
            int k = dfs(to, min(edge[i].c, limit));
            edge[i].c -= k, edge[i ^ 1].c += k;
            limit -= k, flow += k;
            if (flow == limit) break;
        }
    }
    if (!flow) depth[cur] = 0;
    return flow;
}

inline int dinic(int maxFlow = 0) {
    while(bfs()) {
        int tmp;
        while (tmp = dfs(s, INF))
            maxFlow += tmp;
    }
    return maxFlow;
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> m >> n;
    s = 1, t = n;
    fill(head.begin(), head.end(), -1);
    for (int i = 0, u, v, c; i < m; i++) {
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }
    cout << dinic() << endl;
    return 0;
}
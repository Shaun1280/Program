#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P2764 P2764 最小路径覆盖问题
using namespace std;

constexpr int MAXN = 500;
constexpr int INF = 0x3f3f3f3f;

struct Edge {
    Edge() = default;
    Edge(int _to, int _c, int _next) : to(_to), c(_c), next(_next) {}
    /*@param c capacity*/
    int to, c, next;
};
vector<Edge> edge;
int n, m, s, t, maxFlow;
array<int, MAXN> head, curv, depth, nxt;

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
    if (cur == t) return limit;
    int flow(0);
    for (int i = curv[cur]; ~i && limit; i = edge[i].next) {
        curv[cur] = i;
        int to = edge[i].to;
        if (edge[i].c && depth[to] == depth[cur] + 1) {
            int k = dfs(to, min(edge[i].c, limit));
            if (!k) continue;
            edge[i].c -= k, edge[i ^ 1].c += k;
            limit -= k, flow += k;
            if (flow == limit) break;
            nxt[cur] = to;
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

//最小路径覆盖 = n - G'最大流
//G中(u, v)->G'(u, v + n)
//s -> [1, n] && [n + 1, 2n] -> t
int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    s = 0, t = 2 * n + 1;
    fill(head.begin(), head.end(), -1);
    for (int i = 1; i <= n; i++) addEdge(s, i, 1);
    for (int i = n + 1; i <= 2 * n; i++) addEdge(i, t, 1);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        addEdge(u, v + n, 1);
    }
    maxFlow = n;
    maxFlow -= dinic();
    for (int i = 1; i <= n; i++) { //求路径
        if (nxt[i]) {
            int cur = i;
            do {
                if (cur > n) cur -= n;
                cout << cur << " ";
                int to = nxt[cur];
                nxt[cur] = 0;
                cur = to;
            } while (cur != t && cur);
            cout << '\n';
        }
    }
    cout << maxFlow << '\n';
    return 0;
}
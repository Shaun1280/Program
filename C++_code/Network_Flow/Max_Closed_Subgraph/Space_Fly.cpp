#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P2762 P2762 太空飞行计划问题
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

int dinic(int cur, int limit) {
    if (cur == t) return limit;
    int flow(0);
    for (int i = curv[cur]; ~i; i = edge[i].next) {
        curv[cur] = i;
        int to = edge[i].to;
        if (edge[i].c && depth[to] == depth[cur] + 1) {
            int k = dinic(to, min(edge[i].c, limit));
            edge[i].c -= k, edge[i ^ 1].c += k;
            limit -= k, flow += k;
        }
    }
    if (flow == 0) depth[cur] = 0;
    return flow;
}
//depth为0表示在最大流网络上
inline void print() {
    set<int> exp, equip;
    for (int i = 1; i <= m; i++) if (depth[i]) exp.insert(i);
    for (int i = m + 1; i <= m + n; i++) if (depth[i]) equip.insert(i - m);
    for (auto& i : exp) cout << i << " "; cout << endl;
    for (auto& i : equip) cout << i << " "; cout << endl;
}
//最大闭合子图权值 = Σ正点权值-最小割
int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> m >> n;
    s = 0, t = m + n + 1;
    fill(head.begin(), head.end(), -1);
    for (int i = 1, c, v; i <= m; i++) {
        cin >> c, maxFlow += c;
        addEdge(s, i, c);
        while (cin >> v) {
            addEdge(i, v + m, INF);
            if (cin.get() == '\n') break;
        }
    }
    for (int i = m + 1, c; i <= m + n; i++)
        cin >> c, addEdge(i, t, c);
    while(bfs()) maxFlow -= dinic(s, INF);
    print();
    cout << maxFlow << endl;
    return 0;
}
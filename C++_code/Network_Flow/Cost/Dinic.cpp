#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P3381 P3381 【模板】最小费用最大流
using namespace std;

constexpr int MAXN = 5e3 + 3;
constexpr int INF = 0x3f3f3f3f;

template <typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct Edge {
    Edge() = default;
    Edge(int _to, int _c, int _w, int _next) {
        to = _to, c = _c, w = _w, next = _next;
    }
    /*@param c capacity @param w cost*/
    int to, c, w, next;
};
vector<Edge> edge;
array<int, MAXN> head, curv, inq, cost, vis;
int s, t, n, m;

inline void add(int from, int to, int c, int w) {
    //反边初始容量为0 费用为负
    edge.emplace_back(to, c, w, head[from]), head[from] = edge.size() - 1;
    edge.emplace_back(from, 0, -w, head[to]), head[to] = edge.size() - 1;
}

inline bool spfa() {
    fill(cost.begin(), cost.end(), INF);
    fill(inq.begin(), inq.end(), 0);
    copy(head.begin(), head.end(), curv.begin());
    queue<int> q;
    q.push(s), cost[s] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        inq[cur] = false;
        for (int i = head[cur]; ~i; i = edge[i].next) {
            int to = edge[i].to, w = edge[i].w;
            if (cost[to] > cost[cur] + w && edge[i].c) {
                cost[to] = cost[cur] + w;
                if (!inq[to]) q.push(to), inq[to] = true;
            }
        }
    }
    return cost[t] == INF ? false : true;
}

int dfs(int cur, int limit) {
    if (!limit || cur == t) return limit;
    int flow = 0;
    vis[cur] = true;
    for (int i = curv[cur]; ~i; i = edge[i].next) {
        int to = edge[i].to, w = edge[i].w;
        if (!vis[to] && edge[i].c && cost[to] == cost[cur] + w) {
            curv[cur] = i;
            int k = dfs(to, min(limit, edge[i].c));
            edge[i].c -= k, edge[i ^ 1].c += k;
            limit -= k, flow += k;
            if (limit == flow) break;
        }
    }
    vis[cur] = false;
    if (flow == 0) cost[cur] = INF;
    return flow;
}

inline void dinic() {
    int maxFlow(0), minCost(0);
    while (spfa()) {
        int flow;
        while (flow = dfs(s, INF)) {
            maxFlow += flow;
            minCost += cost[t] * flow;
        }
    }
    cout << maxFlow << " " << minCost << endl;
}

int main() {
    read(n), read(m), read(s), read(t);
    fill(head.begin(), head.end(), -1);
    for (int i = 1; i <= m; i++) {
        int u, v, c, w;
        read(u), read(v), read(c), read(w);
        add(u, v, c, w);
    }
    dinic();
    return 0;
}
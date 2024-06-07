#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/UVA1658 UVA1658 海军上将 Admiral
using namespace std;

constexpr int MAXN = 1e5 + 5;
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

inline void addEdge(int from, int to, int c, int w) {
    //反边初始容量为0 费用为负
    edge.push_back(Edge(to, c, w, head[from])), head[from] = edge.size() - 1;
    edge.push_back(Edge(from, 0, -w, head[to])), head[to] = edge.size() - 1;
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

int dinic(int cur, int limit) {
    if (!limit || cur == t) return limit;
    int flow = 0;
    vis[cur] = true;
    for (int i = curv[cur]; ~i; i = edge[i].next) {
        int to = edge[i].to, w = edge[i].w;
        if (!vis[to] && edge[i].c && cost[to] == cost[cur] + w) {
            curv[cur] = i;
            int k = dinic(to, min(limit, edge[i].c));
            edge[i].c -= k, edge[i ^ 1].c += k;
            limit -= k, flow += k;
        }
    }
    vis[cur] = false;
    if (flow == 0) cost[cur] = INF;
    return flow;
}

int main() {
    while (cin >> n >> m) {
        s = 0, t = 2 * n + 1;
        fill(head.begin(), head.end(), -1);
        edge.clear();
        for (int i = 1; i <= n; i++)
            if (i == 1 || i == n) addEdge(i, i + n, 2, 0);
            else addEdge(i, i + n, 1, 0);
        addEdge(s, 1, 2, 0), addEdge(2 * n, t, 2, 0);
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            read(u), read(v), read(w);
            addEdge(u + n, v, 1, w);
        }
        int maxFlow(0), minCost(0);
        while (spfa()) {
            int flow = dinic(s, INF);
            maxFlow += flow;
            minCost += cost[t] * flow;
        }
        cout << minCost << endl;
    }
    return 0;
}
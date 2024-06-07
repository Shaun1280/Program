#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P4174 P4174 [NOI2006]最大获利
using namespace std;

constexpr int MAXN = 1e6 + 6;
constexpr int INF = 0x3f3f3f3f;

struct Edge {
    Edge() = default;
    Edge(int _to, int _c, int _next) : to(_to), c(_c), next(_next) {}
    /*@param c capacity*/
    int to, c, next;
} edge[MAXN];
int n, m, s, t, ans;
array<int, MAXN> head, curv, depth;

inline void addEdge(int from, int to, int c) {
    static int tot;
    edge[tot] = Edge(to, c, head[from]), head[from] = tot++;
    edge[tot] = Edge(from, 0, head[to]), head[to] = tot++;
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

//最大闭合子图权值 = Σ正点权值-最小割
int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    s = 0, t = n + m + 1;
    fill(head.begin(), head.end(), -1);
    for (int i = 1, c; i <= n; i++) {
        cin >> c;
        addEdge(i, t, c);
    }
    for (int i = n + 1, a, b, c; i <= n + m; i++) {
        cin >> a >> b >> c;
        ans += c;
        addEdge(s, i, c);
        addEdge(i, a, INF), addEdge(i, b, INF);
    }
    ans -= dinic();
    cout << ans << endl;
    return 0;
}
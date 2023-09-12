#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P2740
const int MAXN = 55;
const int MAXM = 1e4 + 4;
const int Inf = 0x3f3f3f3f;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
struct E {
    int to, c, next;
    E() {}
    E(int _to, int _c, int _next) { to = _to, c = _c, next = _next; }
} Edge[MAXM << 1];
int head[MAXN << 1], tot(1);
int n, m, maxFlow, s, t;
int depth[MAXN << 1], curv[MAXN << 1];
inline void add(int from, int to, int c) {
    Edge[++tot] = E(to, c, head[from]), head[from] = tot;
}
inline bool bfs() {
    memset(depth, 0, sizeof(depth));
    memcpy(curv, head, sizeof(head));
    queue<int> q;
    q.push(s), depth[s] = 1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = head[cur]; i; i = Edge[i].next) {
            int to = Edge[i].to;
            if (!Edge[i].c || depth[to]) continue;
            depth[to] = depth[cur] + 1;
            q.push(to);
            if (to == t) return true;
        }
    }
    return false;
}
int dinic(int cur, int limit) {
    if (cur == t) return limit;
    int flow = 0;
    for (int i = curv[cur]; ~i; i = Edge[i].next) {
        curv[cur] = i;
        int to = Edge[i].to;
        if (Edge[i].c && depth[to] == depth[cur] + 1) {
            int k = dinic(to, min(Edge[i].c, limit));
            if (k == 0) continue;
            Edge[i].c -= k;
            Edge[i ^ 1].c += k;
            limit -= k, flow += k;
        }
    }
    if (flow == 0) depth[cur] = 0;
    return flow;
}
int u[MAXM], v[MAXM], f, testCase;
int main() {
    cin >> testCase;
    while (testCase--) {
        cin >> n >> m;
        f = Inf;
        for (int i = 1; i <= m; i++) u[i] = read(), v[i] = read();
        for (s = 0; s < n; s++)
            for (t = 0; t < n; t++) {
                if (s == t) continue;
                memset(head, 0, sizeof(head));
                tot = 1, maxFlow = 0;
                for (int i = 0; i < n; i++)
                    if (i == s || i == t)
                        add(i, i + n, Inf), add(i + n, i, 0);
                    else
                        add(i, i + n, 1), add(i + n, i, 0);
                for (int i = 1; i <= m; i++)
                    add(u[i] + n, v[i], Inf), add(v[i], u[i] + n, 0),
                        add(v[i] + n, u[i], Inf), add(u[i], v[i] + n, 0);
                while (bfs()) maxFlow += dinic(s, Inf);
                f = min(f, maxFlow);
            }
        if (n <= 1 || f == Inf) f = n;
        cout << f << endl;
    }
    return 0;
}
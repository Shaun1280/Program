#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 4;
constexpr int MAXM = 1e5 + 5;
constexpr int Inf = 0x3f3f3f3f;

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
int head[MAXN], incf[MAXN], pre[MAXN], tot, inq[MAXN];

inline void add(int from, int to, int c) {
    Edge[tot] = E(to, c, head[from]), head[from] = tot++;
}

inline bool bfs(int s, int t) {
    memset(inq, 0, sizeof(inq));
    queue<int> q;
    q.push(s);
    inq[s] = true, incf[s] = Inf;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = head[cur]; ~i; i = Edge[i].next) {
            if (!Edge[i].c) continue;
            int to = Edge[i].to;
            if (!inq[to]) {
                incf[to] = min(incf[cur], Edge[i].c);
                pre[to] = i, inq[to] = true;
                q.push(to);
                if (to == t) return true;
            }
        }
    }
    return false;
}

inline void update(int s, int t, int &maxFlow) {
    int x = t;
    while (x != s) {
        int i = pre[x];
        Edge[i].c -= incf[t];
        Edge[i ^ 1].c += incf[t];
        x = Edge[i ^ 1].to;
    }
    maxFlow += incf[t];
}

int n, m, s, t, maxFlow;

int main() {
    n = read(), m = read(), s = read(), t = read();
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        u = read(), v = read(), c = read();
        add(u, v, c), add(v, u, 0);
    }
    while (bfs(s, t)) update(s, t, maxFlow);
    cout << maxFlow << endl;
    return 0;
}
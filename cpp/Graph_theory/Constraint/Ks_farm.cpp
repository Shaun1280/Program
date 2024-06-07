#include <bits/stdc++.h>

constexpr int MAXE = 3e4 + 1;
constexpr int MAXP = 1e4 + 1;

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x * f;
}

struct node {
    int to, w, next;
    node() {}
    node(int _to, int _w, int _next) { to = _to, w = _w, next = _next; }
} Edge[MAXE];
int n, m, cnt, head[MAXP];

inline void add_edge(int from, int to, int w) {
    Edge[cnt] = node(to, w, head[from]);
    head[from] = cnt++;
}

int dis[MAXP], inq[MAXP], Cnt[MAXP];

inline bool spfa() {
    deque<int> q;
    memset(dis, 0x3f, sizeof(dis)), dis[0] = 0;
    q.push_front(0), inq[0] = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop_front();
        inq[cur] = false;
        for (int i = head[cur]; ~i; i = Edge[i].next) {
            int to = Edge[i].to;
            if (dis[to] > dis[cur] + Edge[i].w) {
                dis[to] = dis[cur] + Edge[i].w;
                if (!inq[to]) {
                    if (q.empty() || dis[to] < dis[q.front()])
                        q.push_front(to);
                    else
                        q.push_back(to);
                    inq[to] = true;
                    Cnt[to] = Cnt[cur] + 1;
                    if (Cnt[to] > n) return false;
                }
            }
        }
    }
    return true;
}

int main() {
    n = read(), m = read();
    memset(head, -1, sizeof(head));
    int type, a, b, c;
    for (int i = 1; i <= m; i++) {
        type = read();
        switch (type) {
            case 1:
                a = read(), b = read(), c = read();
                add_edge(a, b, -c);
                break;
            case 2:
                a = read(), b = read(), c = read();
                add_edge(b, a, c);
                break;
            case 3:
                a = read(), b = read();
                add_edge(a, b, 0), add_edge(b, a, 0);
                break;
        }
    }
    for (int i = 1; i <= n; i++) add_edge(0, i, 0);
    cout << (spfa() ? "Yes" : "No");
    return 0;
}
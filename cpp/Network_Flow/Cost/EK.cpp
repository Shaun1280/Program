#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P2045
//建图 + K取方格数
using namespace std;

constexpr int MAXN = 5e3 + 5;
constexpr int negaInf = 0xcfcfcfcf;
constexpr int Inf = 0x3f3f3f3f;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

struct node {
    int to, next, c, w;
    node() {}
    node(int _to, int _c, int _w, int _next) {
        to = _to, c = _c, w = _w, next = _next;
    }
};
vector<node> Edge;
int head[MAXN], tot;
inline void add(int from, int to, int c, int w) {
    Edge.push_back(node(to, c, w, head[from])), head[from] = tot++;
    Edge.push_back(node(from, 0, -w, head[to])), head[to] = tot++;
}

int inq[MAXN], cost[MAXN], incf[MAXN], pre[MAXN];
int n, k, ans;
inline int getId(int r, int c, int k) { return (r - 1) * n + c + k * n * n; }

inline bool spfa(int s, int t) {
    queue<int> q;
    memset(cost, 0xcf, sizeof(cost));
    memset(inq, 0, sizeof(inq));
    q.push(s);
    inq[s] = true, cost[s] = 0, incf[s] = Inf;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        inq[cur] = false;
        for (int i = head[cur]; ~i; i = Edge[i].next) {
            if (!Edge[i].c) continue;  //剩余容量为0 不在残量网络中
            int to = Edge[i].to, w = Edge[i].w;
            if (cost[to] < cost[cur] + w) {
                cost[to] = cost[cur] + w;
                incf[to] = min(incf[cur], Edge[i].c);
                pre[to] = i;
                if (!inq[to]) q.push(to), inq[to] = true;
            }
        }
    }
    return cost[t] == negaInf ? false : true;  //汇点是否能到达
}

inline void update(int s, int t, int &ans) {
    int x = t;
    while (x != s) {
        int i = pre[x];
        Edge[i].c -= incf[t];
        Edge[i ^ 1].c += incf[t];
        x = Edge[i ^ 1].to;
    }
    ans += cost[t] * incf[t];
}

int main() {
    n = read(), k = read();
    memset(head, -1, sizeof(head));
    int s = 1, t = 2 * n * n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int w = read();
            add(getId(i, j, 0), getId(i, j, 1), 1, w);
            add(getId(i, j, 0), getId(i, j, 1), k - 1, 0);
            if (j < n) add(getId(i, j, 1), getId(i, j + 1, 0), k, 0);
            if (i < n) add(getId(i, j, 1), getId(i + 1, j, 0), k, 0);
        }
    while (spfa(s, t)) update(s, t, ans);
    cout << ans;
    return 0;
}
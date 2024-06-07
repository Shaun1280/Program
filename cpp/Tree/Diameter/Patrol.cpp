#include <bits/stdc++.h>
//P3629 [APIO2010]巡逻
//https://shaun118294191.github.io/post/p3629-apio2010xun-luo/
constexpr int MAXN = 1e5 + 5;
constexpr int Inf = 1e9;

using namespace std;
using A = int [MAXN];

template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int n, k, L1, L2, tot, ed;
A pre, dis, head, dp;

struct node {
    int to, next, w;
    node (){}
    node (int _to, int _w, int _next) : to(_to), next(_next), w(_w){}
}Edge[MAXN << 1];

inline void add(int from, int to) {
    Edge[tot] = node(to, 1, head[from]), head[from] = tot++;
    Edge[tot] = node(from, 1, head[to]), head[to] = tot++;
}

inline void dfs(int cur, int fa) {
    for (int i = head[cur]; ~i; i = Edge[i].next) {
        int to = Edge[i].to, w = Edge[i].w;
        if (to == fa) continue;
        dis[to] = dis[cur] + 1, pre[to] = i;
        if (dis[to] > L1) L1 = dis[to], ed = to;
        dfs(to, cur);
    }
}

inline void DP(int cur, int fa) {
    for (int i = head[cur]; ~i; i = Edge[i].next) {
        int to = Edge[i].to, w = Edge[i].w;
        if (to == fa) continue;
        DP(to, cur);
        L2 = max(L2, dp[cur] + dp[to] + w);
        dp[cur] = max(dp[cur], dp[to] + w);
    }
}

int main() {
    //freopen("test.in", "r", stdin);
    read(n), read(k);
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i < n; i++)
        read(u), read(v), add(u, v);
    L1 = -Inf, dfs(1, 0);
    dis[ed] = 0, pre[ed] = -1, L1 = -Inf;
    dfs(ed, 0);
    if (k == 1) cout << 2 * (n - 1) - (L1 - 1) << endl;
    else {
        while (~pre[ed]) {
            Edge[pre[ed]].w = Edge[pre[ed] ^ 1].w = -1;
            ed = Edge[pre[ed] ^ 1].to;
        }
        DP(1, 0);
        cout << 2 * (n - 1) - (L1 - 1) - (L2 - 1);
    }
    return 0;
}

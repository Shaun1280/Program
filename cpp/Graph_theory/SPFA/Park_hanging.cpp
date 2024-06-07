#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P3953 P3953 逛公园
using namespace std;
//有向图 1 到 n 长度不超过 d + k 的最短路( d 为到 n 的最短路长度)
constexpr int MAXN = 1e5 + 5;

template <typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int tc, n, m, k, p, dis[MAXN], dp[MAXN][55], inq[MAXN], vis[MAXN][55];
vector<pair<int, int>> G[MAXN], revG[MAXN];

inline void spfa() {
    fill(dis, dis + n + 1, 0x3f3f3f3f);
    fill(inq, inq + n + 1, 0);
    deque<int> q;
    q.push_back(1), dis[1] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop_front();
        inq[cur] = false;
        for (auto& e : G[cur]) {
            int to = e.first, w = e.second;
            if (dis[to] > dis[cur] + w) {
                dis[to] = dis[cur] + w;
                if (!inq[to]) {
                    if (q.empty() || dis[to] < dis[q.front()])
                        q.push_front(to);
                    else q.push_back(to);
                    inq[to] = true;
                }
            }
        }
    }
}

inline int DP(int cur, int d) { //dp[i][j] 到 i 与最短路相差为 j 的方案数 n 开始
    if (d < 0 || d > k) return 0;
    if (vis[cur][d]) return -1; //该状态是否被访问过
    if (dp[cur][d] != -1) return dp[cur][d];
    int res = 0;
    vis[cur][d] = true;
    for (auto& e : revG[cur]) {
        int to = e.first, w = e.second;
        int tmp = DP(to, d + dis[cur] - (dis[to] + w));
        if (tmp == -1) return -1;
        (res += tmp) %= p;
    }
    if (cur == 1 && !d) res++;
    dp[cur][d] = res;
    vis[cur][d] = false;
    return res;
}

signed main() {
    read(tc);
    for (int i = 1; i <= tc; i++) {
        read(n), read(m), read(k), read(p);
        for (int i = 1; i <= n; i++) {
            G[i].clear(), revG[i].clear();
            for (int j = 0; j <= k; j++) dp[i][j] = -1, vis[i][j] = 0;
        }
        for (int i = 1, u, v, w; i <= m; i++) {
            read(u), read(v), read(w);
            G[u].emplace_back(v, w);
            revG[v].emplace_back(u, w); //反向图 用于记忆化搜索
        }
        spfa(); //求出最短路
        int ans = 0;
        for (int i = 0; i <= k; i++) {
            int tmp = DP(n, i);
            if (tmp == -1) {
                ans = -1;
                break;
            }
            (ans += tmp) %= p;
        }
        printf("%d\n", ans);
    }
    return 0;
}
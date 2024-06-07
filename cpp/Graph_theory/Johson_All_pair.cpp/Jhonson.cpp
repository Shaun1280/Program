#include <bits/stdc++.h>
#define pii pair<long long, long long>
// https://www.luogu.com.cn/problem/P5905
// P5905 【模板】Johnson 全源最短路
using namespace std;

constexpr int MAXN = 3e3 + 3;

int n, m;
vector<vector<pii>> G;
array<long long, MAXN> h, inq, cnt, vis, dis;

inline bool spfa() {
    memset(&h, 0x3f, sizeof(h));
    queue<int> q;
    q.push(0), h[0] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop(), inq[cur] = false;
        for (auto e : G[cur]) {
            int to = e.first, w = e.second;
            if (h[to] > h[cur] + w) {
                h[to] = h[cur] + w;
                if (inq[to]) continue;
                cnt[to] = cnt[cur] + 1, q.push(to), inq[to] = true;
                if (cnt[to] > n) return false;
            }
        }
    }
    return true;
}

inline void dijkstra(int s) {
    memset(&vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) dis[i] = 1e9;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({dis[s] = 0, s});
    while (!q.empty()) {
        int cur = q.top().second;
        q.pop();
        if (vis[cur]) continue;
        for (auto e : G[cur]) {
            int to = e.first, w = e.second;
            if (dis[to] > dis[cur] + w) {
                dis[to] = dis[cur] + w;
                q.push({dis[to], to});
            }
        }
        vis[cur] = true;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    G.resize(n + 1);
    while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w), G[u].push_back({v, w});
    }
    for (int i = 1; i <= n; i++) G[0].push_back({i, 0});
    if (!spfa())
        puts("-1");
    else {
        for (int i = 1; i <= n; i++)
            for (auto &e : G[i]) e.second += h[i] - h[e.first];
        for (int i = 1; i <= n; i++) {
            dijkstra(i);
            long long sum = 0;
            for (long long j = 1; j <= n; j++)
                sum += dis[j] == 1e9 ? j * 1e9 : j * (dis[j] - h[i] + h[j]);
            printf("%lld\n", sum);
        }
    }
    return 0;
}
#include<bits/stdc++.h>

constexpr int MAXN = 2e4 + 4;
//P2634 [国家集训队]聪聪可可
//https://www.luogu.com.cn/problem/P2634
//长度 mod 3 = 0的点对数
using namespace std;

template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

using A = int [MAXN];
A dp, sz, cntDis, vis, dis, vec, vecBig;
vector< pair<int, int> > G[MAXN];
int n, root, tot, res, cnt;

inline void getRoot(int cur, int fa) {
    sz[cur] = 1, dp[cur] = 0;
    for (auto &e : G[cur]) {
        int to = e.first;
        if (vis[to] || fa == to) continue;
        getRoot(to, cur);
        sz[cur] += sz[to];
        dp[cur] = max(dp[cur], sz[to]);
    }
    dp[cur] = max(dp[cur], tot - sz[cur]);
    if (dp[cur] < dp[root]) root = cur;
}

inline void getDis(int cur, int fa) {
    vec[cnt++] = dis[cur];
    for (auto &e : G[cur]) {
        int to = e.first, w = e.second;
        if (vis[to] || fa == to) continue;
        dis[to] = (dis[cur] + w) % 3;
        getDis(to, cur);
    }
}

inline void calc(int cur) { //长度 mod 3 = 0的路径数
    int Cnt(0);
    for (auto &e : G[cur]) {
        int to = e.first, w = e.second;
        if (vis[to]) continue;
        cnt = 0, dis[to] = w % 3, getDis(to, cur);
        for (int i = 0; i < cnt; ++i) {
            res += cntDis[(3 - vec[i]) % 3];
            if (vec[i] % 3 == 0) ++res; //根为端点
        }
        for (int i = 0; i < cnt; ++i)
            vecBig[Cnt++] = vec[i], ++cntDis[vec[i]];
    }
    for (int i = 0; i < Cnt; ++i) cntDis[vecBig[i]] = 0;
}

inline void dfs(int cur) {
    vis[cur] = true, calc(cur);
    for (auto &e : G[cur]) {
        int to = e.first;
        if (vis[to]) continue;
        root = cur, tot = dp[root] = sz[to];
        getRoot(to, root), dfs(root);
    }
}

int main() {
    freopen("test.in", "r", stdin);
    read(n);
    for (int i = 1, u, v, w; i < n; ++i) {
        read(u), read(v), read(w);
        G[u].emplace_back(make_pair(v, w));
        G[v].emplace_back(make_pair(u, w));
    }
    root = 0, tot = dp[root] = n;
    getRoot(1, root), dfs(root);
    res = res * 2 + n;
    int tmp = __gcd(res, n * n);
    cout << res / tmp << "/" << n * n / tmp<< endl;
    return 0;
}
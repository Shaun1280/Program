#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/T123576
constexpr int MAXN = 4e5 + 4;
constexpr int ADD = 3e5 + 3;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
vector<int> G[MAXN];
int w[MAXN], dp[MAXN], sz[MAXN], father[MAXN];
long long res[MAXN], add[MAXN];
int vis[MAXN], dis[MAXN];
pair <int, int> vec[MAXN], vecBig[MAXN];
int n, x, tot, cnt, root;
int cntDis[MAXN << 1], cntDis[MAXN << 1];

inline void getRoot(int cur, int fa) {
    sz[cur] = 1, dp[cur] = 0;
    for (auto &to : G[cur]) {
        if (to == fa || vis[to]) continue;
        getRoot(to, cur);
        sz[cur] += sz[to];
        dp[cur] = max(dp[cur], sz[to]);
    }
    dp[cur] = max(dp[cur], tot - sz[cur]);
    if (dp[cur] < dp[root]) root = cur;
}

inline void getDis(int cur, int fa) {
    add[cur] = 0;
    vec[cnt++] = make_pair(dis[cur], cur);//, cntDis[dis[cur] + ADD]++;
    for (auto &to : G[cur]) {
        if (to == fa || vis[to]) continue;
        dis[to] = dis[cur] + w[to];
        father[to] = cur;
        getDis(to, cur);
    }
}

inline void calc(int cur) {
    int Cnt(0);
    for (auto &to : G[cur]) {
        if (vis[to]) continue;
        cnt = 0, dis[to] = w[to], getDis(to, cur);
        for (int i = 0; i < cnt; i++) {
            int d = vec[i].first;
            res[cur] += cntDis[-1 - w[cur] - d + ADD] + cntDis[-2 - w[cur] - d + ADD];
            if (d + w[cur] == -1 || d + w[cur] == -2) res[cur]++;
        }
        for (int i = 0; i < cnt; i++)
            vecBig[Cnt++] = vec[i], cntDis[vec[i].first + ADD]++; //保存已访问子树的结果
    }
    for (auto &to : G[cur]) {
        if (vis[to]) continue;
        cnt = 0, dis[to] = w[to], getDis(to, cur);
        for (int i = 0; i < cnt; i++) cntDis[vec[i].first + ADD]--;
        for (int i = cnt - 1; i >= 0; i--) {
            int d = vec[i].first, node = vec[i].second;
            add[node] += cntDis[-1 - w[cur] - d + ADD] + cntDis[-2 - w[cur] - d + ADD];
            if (d + w[cur] == -1 || d + w[cur] == -2) add[node]++;
            add[father[node]] += add[node];
            res[node] += add[node];
        }
        for (int i = 0; i < cnt; i++) cntDis[vec[i].first + ADD]++;
    }
    for (int i = 0; i < Cnt; i++) cntDis[vecBig[i].first + ADD] = 0;
}

inline void dfs(int cur) {
    vis[cur] = true, calc(cur);
    for (auto &to : G[cur]) {
        if (vis[to]) continue;
        root = cur, tot = dp[root] = sz[to];
        getRoot(to, root), dfs(root);
    }
}

int main() {
    read(n), read(x);
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    for (int i = 1, tmp; i <= n; i++)
        read(tmp), w[i] = tmp >= x ? 1 : -1;
    root = 0, tot = dp[root] = n;
    getRoot(1, root), dfs(root);
    long long mx = 0;
    for (int i = 1; i <= n; i++) 
        if (w[i] == -1) mx = max(mx, res[i]);
    cout << mx << endl;
    return 0;
}
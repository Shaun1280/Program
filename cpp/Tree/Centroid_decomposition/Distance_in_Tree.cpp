#include<bits/stdc++.h>
constexpr int MAXN = 5e4 + 4;
//https://shaun118294191.github.io/post/cf161d-distance-in-tree/
//CF161D Distance in Tree
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
vector<int> G[MAXN];
int n, k, root, cnt, tot;
long long res;
using A = int [MAXN];
A dp, cntDis, vec, vecBig, sz, dis, vis;
inline void getRoot(int cur, int fa) {
    sz[cur] = 1, dp[cur] = 0;
    for (auto &to : G[cur]) {
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
    for (auto &to :G[cur]) {
        if (vis[to] || to == fa) continue;
        dis[to] = dis[cur] + 1;
        getDis(to, cur);
    }
}
inline void calc(int cur) {
    int Cnt(0);
    for (auto &to : G[cur]) {
        if (vis[to]) continue;
        cnt = 0, dis[to] = 1, getDis(to, cur);
        for (int i = 0; i < cnt; i++) {
            res += cntDis[k - vec[i]];
            if (vec[i] == k) res++; // //子节点到根的路径
        }
        for (int i = 0; i < cnt; i++)
            vecBig[Cnt++] = vec[i], cntDis[vec[i]]++;
    }
    for (int i = 0; i < Cnt; i++) cntDis[vecBig[i]] = 0;
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
    read(n), read(k);
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    root = 0, tot = dp[root] = n;
    getRoot(1, root), dfs(root);
    cout << res << endl;
    return 0;
}
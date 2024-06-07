#include<bits/stdc++.h>
//https://shaun118294191.github.io/post/p3806-mo-ban-dian-fen-zhi-1/
constexpr int MAXN = 1e4 + 4;
using namespace std;
template<typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
vector< pair<int, int> > G[MAXN];
int n, m, tot, cnt, root;
int sz[MAXN], dp[MAXN], vis[MAXN];
int query[MAXN], res[MAXN];
int vec[MAXN], dis[MAXN], cntDis[MAXN];
inline void getRoot(int cur, int fa) { //求树的重心 自上而下
    sz[cur] = 1, dp[cur] = 0;
    for (auto &e : G[cur]) {
        int to = e.first, w = e.second;
        if (to == fa || vis[to]) continue;
        getRoot(to, cur);
        sz[cur] += sz[to];
        dp[cur] = max(dp[cur], sz[to]);
    }
    dp[cur] = max(dp[cur], tot - sz[cur]);
    if (dp[cur] < dp[root]) root = cur;
}
inline void getDis(int cur, int fa) { //求出到根root的距离
    if (dis[cur] <= 1e7) 
        vec[cnt++] = dis[cur], cntDis[dis[cur]]++;
    for (auto &e : G[cur]) {
        int to = e.first, w = e.second;
        if (to == fa || vis[to]) continue;
        dis[to] = dis[cur] + w;
        getDis(to, cur);
    }
}
inline void calc(int cur, int w, int type) { //cur为有根树的根节点(重心)
    cnt = 0, dis[cur] = w, getDis(cur, 0);
    for (int j = 1; j <= m; j++)
        for (int i = 0; i < cnt; i++)
            if (vec[i] <= query[j]) res[j] += type * cntDis[vec[i]] * cntDis[query[j] - vec[i]];
    for (int i = 0; i < cnt; i++) cntDis[vec[i]] = false;
}
inline void dfs(int cur) {
    vis[cur] = true, calc(cur, 0, 1);
    for (auto &e : G[cur]) {
        int to = e.first, w = e.second;
        if (vis[to]) continue;
        calc(to, w, -1); //容斥 减去儿子中的路径数 注意要加上w
        root = cur, tot = dp[root] = sz[to]; //准备重新选择根节点
        getRoot(to, root), dfs(root);
    }
}
int main() {
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    read(n), read(m);
    for (int i = 1, u, v, w; i < n; i++) {
        read(u), read(v), read(w);
        G[u].emplace_back(make_pair(v, w)), G[v].emplace_back(make_pair(u, w));
    }
    for (int i = 1; i <= m; i++) read(query[i]);
    root = 0, tot = dp[root] = n;
    getRoot(1, root), dfs(root);
    for (int i = 1; i <= m; i++)
        res[i] > 0 ? puts("AYE") : puts("NAY");
    return 0;
}
#include<bits/stdc++.h>
//https://shaun118294191.github.io/post/p4178-tree/
constexpr int MAXN = 4e4 + 4;
using namespace std;
template<typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
vector< pair<int, int> > G[MAXN];
vector<int> vec;
int n, k, tot, root, res;
int sz[MAXN], dp[MAXN], dis[MAXN], vis[MAXN];
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
    vec.emplace_back(dis[cur]);
    for (auto &e : G[cur]) {
        int to = e.first, w = e.second;
        if (to == fa || vis[to]) continue;
        dis[to] = dis[cur] + w;
        getDis(to, cur);
    }
}
inline void calc(int cur, int w, int type) { //cur为有根树的根节点(重心) type为1表示加
    dis[cur] = w, vec.clear(), getDis(cur, 0);
    sort(vec.begin(), vec.end());
    int l = 0, r = (int)vec.size() - 1;
    while (l <= r) {
        if (vec[l] + vec[r] <= k) res += type * (r - l), ++l;
        else --r;
    }
}
inline void dfs(int cur) {
    vis[cur] = true, calc(root, 0, 1);
    for (auto &e : G[cur]) {
        int to = e.first, w = e.second;
        if (vis[to]) continue;
        calc(to, w, -1); //容斥思想 减去儿子中的路径数 注意要加上w
        root = cur, tot = dp[root] = sz[to]; //准备重新选择根节点
        getRoot(to, root), dfs(root);
    }
}
int main() {
    read(n);
    for (int i = 1, u, v, w; i < n; i++) {
        read(u), read(v), read(w);
        G[u].emplace_back(make_pair(v, w)), G[v].emplace_back(make_pair(u, w));
    }
    read(k);
    root = 0, tot = dp[root] = n;
    getRoot(1, root), dfs(root);
    cout << res << endl;
    return 0;
}
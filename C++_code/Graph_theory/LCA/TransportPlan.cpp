#include<bits/stdc++.h>
//P2680 运输计划
//https://www.luogu.com.cn/problem/P2680
constexpr int MAXN = 3e5 + 5;
constexpr int LOG = 20;
using namespace std;
using A = int [MAXN];
template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
int n, m, f[MAXN][LOG], tot;
int need, provide, cnt;
A depth, delta, dis, head;
struct node {
    int to, w, next;
    node(){}
    node(int _to, int _w, int _next) : to(_to), w(_w), next(_next){}
}Edge[MAXN << 1];
inline void add(int from, int to, int w) {
    Edge[tot] = node(to, w, head[from]), head[from] = tot++;
    Edge[tot] = node(from, w, head[to]), head[to] = tot++;
}
pair<pair<int, int>, int> vec[MAXN];
inline void dfs(int cur, int fa) {
    depth[cur] = depth[fa] + 1, f[cur][0] = fa;
    for (int i = 1; i < LOG; i++)
        f[cur][i] = f[f[cur][i - 1]][i - 1];
    for (int i = head[cur]; ~i; i = Edge[i].next) {
        int to = Edge[i].to, w = Edge[i].w;
        if (to == fa) continue;
        dis[to] = dis[cur] + w;
        dfs(to, cur);
    }
}
inline int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--)
        if (depth[f[u][i]] >= depth[v])
            u = f[u][i];
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--)
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}
inline void getCnt(int cur, int fa, int w) { //w与父亲之间的距离
    for (int i = head[cur]; ~i; i = Edge[i].next) {
        int to = Edge[i].to, w = Edge[i].w;
        if (to == fa) continue;
        getCnt(to, cur, w);
        delta[cur] += delta[to];
    }
    if (w >= need) provide = max(provide, delta[cur]);
}
inline bool check(int mid) {
    need = 0, provide = 0, cnt = 0;
    memset(delta, 0, sizeof(delta));
    for (int i = 1; i <= m; i++) {
        int u = vec[i].first.first, v = vec[i].first.second, lca = vec[i].second;
        int d = dis[u] + dis[v] - 2 * dis[lca];
        if (d > mid) {
            delta[u]++, delta[v]++, delta[lca] -= 2;
            cnt++, need = max(need, d - mid);
        }
    }
    getCnt(1, 0, 0);
    return provide >= cnt;
}
int main() {
    read(n), read(m);
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v, t; i < n; i++) {
        read(u), read(v), read(t);
        add(u, v, t);
    }
    dfs(1, 0);
    for (int i = 1, u, v, lca; i <= m; i++) {
        read(u), read(v), lca = LCA(u, v);
        vec[i] = make_pair(make_pair(u, v), lca);
    }
    int l = 0, r = 3e8, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans << endl;
    return 0;
}
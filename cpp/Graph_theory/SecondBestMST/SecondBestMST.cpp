#include<bits/stdc++.h>
//https://www.luogu.com.cn/blog/user48611/p4180-mu-ban-yan-ge-ci-xiao-sheng-cheng-shu-bjwc2010-post
typedef long long LL;
constexpr int MAXM = 3e5 + 5;
constexpr int MAXN = 1e5 + 5;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
vector< pair<int, pair <int, int> > >vec;
struct node {
    int to, next, w;
    node(){}
    node(int _to, int _next, int _w) {
        to = _to, next = _next, w = _w;
    }
}Edge[MAXM << 1];
int n, m, delta(0x3f3f3f3f);
int head[MAXN], tot, inTree[MAXM << 1], fa[MAXN], depth[MAXN];
int f[MAXN][20], val[MAXN][20];
inline int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void Union(int a, int b) {
    int r1 = find(a), r2 = find(b);
    if(r1 != r2) fa[r1] = r2;
}
inline void add(int from, int to, int w) {
    Edge[tot] = node(to, head[from], w), head[from] = tot++;
    Edge[tot] = node(from, head[to], w), head[to] = tot++;
}
inline void Init() {
    memset(head, -1, sizeof(head));
    n = read(), m = read();
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read();
        vec.push_back(make_pair(w, make_pair(u, v)));
    }
}
inline LL kruskal(LL sum) {
    sort(vec.begin(), vec.end());
    for (int i = 0, cnt = 0; i < vec.size(); i++) {
        int from = vec[i].second.first, to = vec[i].second.second;
        if (find(from) != find(to)) {
            Union(from, to);
            cnt++, sum += vec[i].first;
            inTree[i] = true;
            add(from, to, vec[i].first);
        }
        if (cnt == n - 1) break;
    }
    return sum;
}
void dfs(int cur, int fa, LL w) {
    depth[cur] = depth[fa] + 1;
    f[cur][0] = fa, val[cur][0] = w; //0级祖先为fa
    for (int i = 1; i < 20; i++) //LCA预处理
        f[cur][i] = f[f[cur][i - 1]][i - 1],
        val[cur][i] = max(val[cur][i - 1], val[f[cur][i - 1]][i - 1]);
        //second = max(min(g[u][i−1],g[f[u][i−1]][i−1]),max(h[u][i−1],h[f[u][i−1]][i−1])))
        //g[u][i] = max (g[u][i - 1], g[f[u][i - 1]][i - 1]);
        //h[u][i] = max (h[u][i - 1], h[f[u][i - 1]][i - 1]);
        //if (g[u][i - 1] > g[f[u][i - 1]][i - 1]) h[u][i] = max (h[u][i], g[f[u][i - 1]][i - 1]);
        //else if (g[u][i - 1] < g[f[u][i - 1]][i - 1]) h[u][i] = max (h[u][i], g[u][i - 1]);
    for (int i = head[cur]; ~i; i = Edge[i].next) {
        int to = Edge[i].to;
        if (fa == to) continue;
        dfs(to, cur, Edge[i].w);
    }
}
inline int LCA(int u, int v, int w, int Max) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = 19; i >= 0; i--)
        if (depth[f[u][i]] >= depth[v]) {
            Max = max(Max, val[u][i] == w ? 0 : val[u][i]);
            u = f[u][i];
        }
    if (u == v) return Max;
    for (int i = 19; i >= 0; i--)
        if (f[u][i] != f[v][i]) {
            Max = max(Max, max(val[u][i] == w ? 0 : val[u][i], val[v][i] == w ? 0 : val[v][i]));
            u = f[u][i], v = f[v][i];
        }
    return max(Max, max(val[u][0] == w ? 0 : val[u][0], val[v][0] == w ? 0 : val[v][0]));
}
int main(){
    Init();
    LL sum = kruskal(0);
    for (int i = 1; i <= n; i++)
        if (!depth[i]) dfs(i, 0, 0);
    for (int i = 0; i < vec.size(); i++) {
        if(inTree[i]) continue;
        int u = vec[i].second.first, v = vec[i].second.second, w = vec[i].first;
        int Max = LCA(u, v, w, 0);  
        delta = min(delta, w - Max);
    }
    cout << sum + delta;
    return 0;
}
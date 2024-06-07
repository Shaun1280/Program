#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P2515
using namespace std;
//P2515 [HAOI2010]软件安装
template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 202, MOD = 1e9 + 7;

int n, m, tot, tim, dp[MAXN][505], ans;
array<int, MAXN> v, w, sz, dfn, from, belong, in, pre, fa;
vector<int> g[MAXN], G[MAXN];

template<typename T>
inline void Max(T& a, T b) { a = a > b ? a : b; }

inline void init(int cur) {
    belong[cur] = tot, w[tot] += w[cur], v[tot] += v[cur];
    for (auto& to: g[cur]) {
        if (belong[to] == tot || !in[to]) continue;
        init(to);
    }
}

void topoSort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) if (!in[i]) q.push(i);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (fa[cur] && !(--in[fa[cur]])) q.push(fa[cur]);
    }
    for (int i = 1; i <= n; i++)
        if (in[i] && belong[i] == i) ++tot, init(i); //处理环
    for (int i = 1; i <= n; i++)
        for (auto& to : g[i]) //这里不会有一个点同时连接同一个环的两个节点
            if (belong[i] != belong[to]) G[belong[i]].push_back(belong[to]);
    for (int i = 1; i <= tot; i++) //虚拟节点向 i 加边
        if (!fa[i]) G[0].push_back(i);
}

void dfs(int cur, int f) { //树上预处理
    sz[cur] = 1, dfn[cur] = ++tim, from[tim] = cur;
    for (auto& to : G[cur]) {
        if (to == f) continue;
        pre[to] = pre[cur] + w[cur];
        dfs(to, cur);
        sz[cur] += sz[to];
    }
}

int main() {
    read(n, m), tot = n;
    for (int i = 1; i <= n; i++) read(w[i]);
    for (int i = 1; i <= n; i++) read(v[i]);
    for (int i = 1; i <= n; i++) {
        read(fa[i]);
        belong[i] = i;
        if (fa[i]) g[fa[i]].push_back(i), in[fa[i]]++; //需要反向增加in[]
    }
    topoSort(); //拓扑排序找环
    dfs(0, 0);
    for (int i = 1; i <= tim; i++) { //dfs序 O(nm)
        for (int j = pre[from[i]]; j <= m; j++) { //from[i]前的节点必须被选 pre为节点w前缀和
            if (j + w[from[i]] <= m) { //选该节点
                Max(dp[i + 1][j + w[from[i]]], dp[i][j] + v[from[i]]);
                Max(ans, dp[i + 1][j + w[from[i]]]);
            } //不选该节点 只能选子树外的节点
            Max(dp[i + sz[from[i]]][j], dp[i][j]);
            Max(ans, dp[i + sz[from[i]]][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
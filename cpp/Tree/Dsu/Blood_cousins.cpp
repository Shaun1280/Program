#include <bits/stdc++.h>
//Blood Cousins 与 v 有 k 级祖先的节点数 转化为 k 级祖先有多少 depth + k 节点
using namespace std;
//https://codeforces.ml/contest/208/problem/E
template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int n, m, tim, fa[MAXN][19];
array<int, MAXN>sz, hson, depth, in, from, cnt, res;
vector<int> G[MAXN];
vector<pair<int, int>> q[MAXN];

void init(int cur, int f) {
    sz[cur] = 1, depth[cur] = depth[f] + 1;
    in[cur] = ++tim, from[tim] = cur;
    for (int i = 1; i < 19; i++)
        fa[cur][i] = fa[fa[cur][i - 1]][i - 1];
    for (auto& to : G[cur]) {
        if (to == f) continue;
        init(to, cur);
        sz[cur] += sz[to];
        if (!hson[cur] || sz[hson[cur]] < sz[to]) hson[cur] = to;
    }
}

inline void add(int cur, int val) { cnt[depth[cur]] += val; }

void dsu(int cur, bool keep) {
    for (auto& to : G[cur]) {
        if (to == fa[cur][0] || to == hson[cur]) continue;
        dsu(to, false);
    }
    if (hson[cur]) dsu(hson[cur], true);
    
    add(cur, 1);
    for (auto& to : G[cur]) {
        if (to == fa[cur][0] || to == hson[cur]) continue;
        for (int j = in[to]; j <= in[to] + sz[to] - 1; j++) add(from[j], 1);
    }
    for (auto& i : q[cur]) {
        res[i.second] = cnt[depth[cur] + i.first];
        if (res[i.second]) res[i.second]--;
    }
    if (keep == false) {
        for (int j = in[cur]; j <= in[cur] + sz[cur] - 1; j++)
            add(from[j], -1);
    }
}

int getFa(int cur, int k) {
    for (int i = 18; ~i; i--)
        if ((1 << i) <= k)
            cur = fa[cur][i], k -= (1 << i);
    return cur;
}

int main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(fa[i][0]);
        if (fa[i][0]) G[fa[i][0]].emplace_back(i);
    }
    for (int i = 1; i <= n; i++)
        if (!fa[i][0]) init(i, 0);
    read(m);
    for (int i = 1, v, p; i <= m; i++) {
        read(v, p);
        q[getFa(v, p)].emplace_back(p, i);
    }
    for (int i = 1; i <= n; i++)
        if (!fa[i][0]) dsu(i, false);
    for (int i = 1; i <= m; i++) printf("%d ", res[i]);
    return 0;
}
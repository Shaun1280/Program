#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF246E
using namespace std;
//子树深度为 depth[v] + p 的节点中不同字符个数
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

int n, m, tim;
array<int, MAXN>fa, sz, hson, depth, in, from, cnt, res;
array<string, MAXN> name;
vector<int> G[MAXN];
vector<pair<int, int>> q[MAXN];

void init(int cur, int f) {
    sz[cur] = 1, depth[cur] = depth[f] + 1;
    in[cur] = ++tim, from[tim] = cur;
    for (auto& to : G[cur]) {
        if (to == f) continue;
        init(to, cur);
        sz[cur] += sz[to];
        if (!hson[cur] || sz[hson[cur]] < sz[to]) hson[cur] = to;
    }
}

unordered_map<string, int> mp[MAXN];
inline void add(int cur, int val) {
    mp[depth[cur]][name[cur]] += val;
    if (!mp[depth[cur]][name[cur]]) mp[depth[cur]].erase(name[cur]);
}

void dsu(int cur, bool keep) {
    for (auto& to : G[cur]) {
        if (to == fa[cur] || to == hson[cur]) continue;
        dsu(to, false);
    }
    if (hson[cur]) dsu(hson[cur], true);
    
    add(cur, 1);
    for (auto& to : G[cur]) {
        if (to == fa[cur] || to == hson[cur]) continue;
        for (int j = in[to]; j <= in[to] + sz[to] - 1; j++) add(from[j], 1);
    }
    for (auto& i : q[cur])
        res[i.second] = mp[depth[cur] + i.first].size();
    if (keep == false) {
        for (int j = in[cur]; j <= in[cur] + sz[cur] - 1; j++)
            add(from[j], -1);
    }
}

int main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        char tmp[21];
        scanf("%s", tmp);
        name[i] = tmp;
        read(fa[i]);
        if (fa[i]) G[fa[i]].emplace_back(i);
    }
    for (int i = 1; i <= n; i++)
        if (!fa[i]) init(i, 0);
    read(m);
    for (int i = 1, v, p; i <= m; i++) {
        read(v, p);
        q[v].emplace_back(p, i);
    }
    for (int i = 1; i <= n; i++)
        if (!fa[i]) dsu(i, false);
    for (int i = 1; i <= m; i++) printf("%d\n", res[i]);
    return 0;
}
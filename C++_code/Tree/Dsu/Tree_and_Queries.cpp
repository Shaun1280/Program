#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF375D
using namespace std;
//子树中出现次数大于 ki 的颜色数目
#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

int n, m, tim;
array<int, MAXN> cnt, sum, hson, fa, sz, col, res, in, from;
vector<int> G[MAXN];
vector<pair<int, int>> query[MAXN];

void init(int cur, int f) {
    sz[cur] = 1, fa[cur] = f, in[cur] = ++tim, from[tim] = cur;
    for (auto& to : G[cur]) {
        if (to == f) continue;
        init(to, cur);
        sz[cur] += sz[to];
        if (!hson[cur] || sz[to] > sz[hson[cur]]) hson[cur] = to;
    }
}

void add(int cur, int f, int val) {
    if (val == 1) ++cnt[col[cur]], ++sum[cnt[col[cur]]];
    else --sum[cnt[col[cur]]], --cnt[col[cur]];
    for (auto& to : G[cur]) {
        if (to == fa[cur] || to == hson[f]) continue;
        add(to, f, val);
    }
}

void dsu(int cur, int keep) {
    for (auto& to : G[cur]) {
        if (to == fa[cur] || to == hson[cur]) continue;
        dsu(to, false);
    }
    if (hson[cur]) dsu(hson[cur], true);
    add(cur, cur, 1);
    for (auto& i : query[cur]) res[i.second] = sum[i.first];
    if (keep == false) hson[cur] = 0, add(cur, cur, -1);
}

int main() {
    read(n, m);
    for (int i = 1; i <= n; i++) read(col[i]);
    for (int i = 1, u, v; i < n; i++) {
        read(u, v);
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    init(1, 0);
    for (int i = 1, u, k; i <= m; i++) {
        read(u, k);
        query[u].emplace_back(k, i); //一个节点可能多次被询问
    }
    dsu(1, true);
    for (int i = 1; i <= m; i++) printf("%d\n", res[i]);
    return 0;
}
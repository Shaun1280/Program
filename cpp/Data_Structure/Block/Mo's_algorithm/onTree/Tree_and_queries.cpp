#include <bits/stdc++.h>
//子树中出现次数大于等于k的颜色数
using namespace std;
//https://www.luogu.com.cn/problem/CF375D dfn +树上莫队
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


int n, m;
array<int, MAXN> col, in, out, from, belong, ans, sum, cnt;
vector<int> G[MAXN];

struct Query {
    int l, r, id, k;
    friend inline bool operator<(const Query& lhs, const Query& rhs) {
        if (belong[lhs.l] == belong[rhs.l]) return lhs.r < rhs.r;
        return lhs.l < rhs.l;
    }
} Q[MAXN];

void dfs(int cur, int fa) {
    static int tim;
    in[cur] = ++tim, from[tim] = cur;
    for (auto& to : G[cur]) {
        if (to == fa) continue;
        dfs(to, cur);
    }
    out[cur] = tim; //链上统计才需要out[cur] = ++tim, from[tim] = cur
}

inline void add(int x) { ++cnt[col[from[x]]], ++sum[cnt[col[from[x]]]]; }

inline void del(int x) { --sum[cnt[col[from[x]]]], --cnt[col[from[x]]];}

int main() {
    read(n, m);
    int base = pow(n, 0.54);
    for (int i = 1; i <= n; i++) read(col[i]);
    for (int i = 1; i <= n; i++) belong[i] = i / base;
    for (int i = 1, u, v; i < n; i++) {
        read(u, v);
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    dfs(1, 0);
    for (int i = 1, u, k; i <= m; i++) {
        read(u, k);
        Q[i].l = in[u], Q[i].r = out[u];
        Q[i].k = k, Q[i].id = i;
    }
    sort(Q + 1, Q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (r < Q[i].r) add(++r);
        while (r > Q[i].r) del(r--);
        while (l < Q[i].l) del(l++);
        while (l > Q[i].l) add(--l);
        ans[Q[i].id] = sum[Q[i].k];
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}
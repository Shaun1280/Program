#include <bits/stdc++.h>
// 线段树优化建图 拓扑排序 https://www.luogu.com.cn/problem/P3588
using namespace std;

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

template<typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}

template<typename T, typename ...Args>
inline void write(T& x , Args&... args) { write(x), putchar('\n'), write(args...); }

constexpr int MAXN = 6e5 + 5, MOD = 1e9 + 7;

#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
struct SegTree { int ls, rs; } tree[MAXN];

int in[MAXN];
vector<pair<int, int>> g[MAXN];
void add(int u, int v, int w) { g[u].emplace_back(v, w); in[v]++; }

int tot;
int buildUp(int x, int l, int r) {
    if (l == r) return l;
    x = ++tot;
    int mid = (l + r) >> 1;
    ls(x) = buildUp(ls(x), l, mid);
    rs(x) = buildUp(rs(x), mid + 1, r);
    add(ls(x), x, 0), add(rs(x), x, 0);
    return x;
};

void link(int x, int l, int r, int ql, int qr, int u) { // 
    if (ql <= l && r <= qr) return add(x, u, 0), void();
    int mid = (l + r) >> 1;
    if (ql <= mid) link(ls(x), l, mid, ql, qr, u);
    if (qr > mid) link(rs(x), mid + 1, r, ql, qr, u);
}

int n, s, m;
int ans[MAXN], should[MAXN];

void topo() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) q.push(i), ans[i] = 1;
        if (should[i]) ans[i] = should[i];
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (const auto& [to, w] : g[cur]) {
            ans[to] = max(ans[to], ans[cur] + w);
            if ((should[to] && ans[to] > should[to]) || ans[to] > 1000000000) return puts("NIE"), void();
            if (!(--in[to])) q.push(to);
        }
    }
    for (int i = 1; i <= n; i++) if (in[i]) return puts("NIE"), void();
    puts("TAK");
    for (int i = 1; i <= n; i++) write(ans[i]), putchar(' ');
}

signed main() {
    read(n, s, m);
    for (int i = 1, p, d; i <= s; i++) read(p, d), should[p] = d;
    tot = n;
    int rootup = buildUp(tot + 1, 1, n);
    for (int i = 1, l, r, k; i <= m; i++) {
        cin >> l >> r >> k;
        vector<int> x(k);
        int mid = tot + i;
        for (int j = 0; j < k; j++) { // 分成不超过 k + 1 个区间，区间连边向虚拟节点
            cin >> x[j];
            if (j == 0) {
                if (x[j] > l) link(rootup, 1, n, l, x[j] - 1, mid);
            }
            else {
                if (x[j - 1] + 1 <= x[j] - 1) link(rootup, 1, n, x[j - 1] + 1, x[j] - 1, mid);
            }
        }
        if (x[k - 1] < r) link(rootup, 1, n, x[k - 1] + 1, r, mid);
        for (int j = 0; j < k; j++) add(mid, x[j], 1); // 虚拟节点向 k 个点连 1 边，表示至少大 1
    }
    topo();
    return 0;
}
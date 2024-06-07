#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/CF786B CF786B Legacy
// 线段树优化建图 两颗线段是 一颗用于 u -> [l, r]， 另一颗用于 [l, r] -> u 公用叶子节点
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
struct SegTree { int ls, rs; } tree[MAXN << 2];

vector<pair<int, int>> g[MAXN << 2];
void add(int u, int v, int w) { g[u].emplace_back(v, w); }

int tot;
int buildDown(int x, int l, int r) {
    if (l == r) return l;
    x = ++tot;
    int mid = (l + r) >> 1;
    ls(x) = buildDown(ls(x), l, mid);
    rs(x) = buildDown(rs(x), mid + 1, r);
    add(x, ls(x), 0), add(x, rs(x), 0);
    return x;
};


int buildUp(int x, int l, int r) {
    if (l == r) return l;
    x = ++tot;
    int mid = (l + r) >> 1;
    ls(x) = buildUp(ls(x), l, mid);
    rs(x) = buildUp(rs(x), mid + 1, r);
    add(ls(x), x, 0), add(rs(x), x, 0);
    return x;
}

void link(int x, int l, int r, int ql, int qr, int u, int w, int up) {
    if (ql <= l && r <= qr) { // type = 0 then u -> [l, r] else [l, r] -> u
        up ? add(x, u, w) : add(u, x, w);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) link(ls(x), l, mid, ql, qr, u, w, up);
    if (qr > mid) link(rs(x), mid + 1, r, ql, qr, u, w, up);
}

int n, q, s;
long long dis[MAXN << 2];
bool vis[MAXN << 2];

void dijkstra(int s) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    memset(dis, 0x3f, sizeof(dis));
    q.emplace(dis[s] = 0, s);
    while (!q.empty()) {
        auto [d, cur] = q.top();
        q.pop();
        if (vis[cur]) continue;
        for (auto& [to, w] : g[cur]) {
            if (vis[to]) continue;
            if (dis[to] > d + w) {
                dis[to] = d + w;
                q.emplace(dis[to], to);
            }
        }
        vis[cur] = true;
    }
}

int main() {
    boost;
    cin >> n >> q >> s, tot = n;
    int rootdown = buildDown(tot + 1, 1, n), rootup = buildUp(tot + 1, 1, n);
    for (int i = 1; i <= q; i++) {
        int op, u, l, r, v, w;
        cin >> op;
        if (op == 1) {
            cin >> u >> v >> w;
            add(u, v, w);
        } else if (op == 2) {
            cin >> u >> l >> r >> w;
            link(rootdown, 1, n, l, r, u, w, 0);
        } else if (op == 3) {
            cin >> u >> l >> r >> w;
            link(rootup, 1, n, l, r, u, w, 1);
        }
    }
    dijkstra(s);
    for (int i = 1; i <= n; i++) cout << (dis[i] == 0x3f3f3f3f3f3f3f3f ? -1 : dis[i]) << " ";
    return 0;
}
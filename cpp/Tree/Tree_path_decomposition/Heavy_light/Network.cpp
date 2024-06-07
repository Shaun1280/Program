#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P3250 树链剖分 + 线段树维护双堆
using namespace std;

constexpr int MAXN = 2e5 + 5;

int n, m, root, ans;
array<int, MAXN> fa, depth, sz, rnk, in, top, hSon, val;
vector<int> G[MAXN];
pair<pair<int, int>, int> event[MAXN];

struct SegTree {
    int lson, rson;
    int l, r;
    priority_queue<int, vector<int>, less<int>> add, del;
    //当 add 和 del 堆顶相同时，删除
} tree[MAXN << 1];

inline void build(int& root, int l = 1, int r = n) {
    static int tot;
    root = tot++, tree[root].l = l, tree[root].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(tree[root].lson, l, mid), build(tree[root].rson, mid + 1, r);
}

inline void update(int& root) {
    while (tree[root].add.size() && tree[root].del.size() && tree[root].add.top() == tree[root].del.top())
        tree[root].add.pop(), tree[root].del.pop();
}

inline void modify(int& root, int l, int r, int val) {
    if (l <= tree[root].l && tree[root].r <= r) {
        if (val > 0) tree[root].add.push(val);
        else tree[root].del.push(-val);
        update(root);
        return;
    }
    update(root);
    int mid = (tree[root].l + tree[root].r) >> 1;
    if (l <= mid) modify(tree[root].lson, l, r, val);
    if (r > mid) modify(tree[root].rson, l, r, val);
}

inline void ask(int& root, int pos) { //不需要延迟标记
    update(root);
    if (!tree[root].add.size()) ans = max(ans, -1);
    else ans = max(ans, tree[root].add.top());
    if (tree[root].l == tree[root].r) return;
    int mid = (tree[root].l + tree[root].r) >> 1;
    if (pos <= mid) ask(tree[root].lson, pos);
    else ask(tree[root].rson, pos);
}
/*---------------------------------------*/
inline void dfs1(int cur, int f) {
    sz[cur] = 1, fa[cur] = f, depth[cur] = depth[f] + 1;
    for (auto& to : G[cur]) {
        if (to == f) continue;
        dfs1(to, cur);
        sz[cur] += sz[to];
        if (!hSon[cur] || sz[to] > sz[hSon[cur]]) hSon[cur] = to;
    }
}

inline void dfs2(int cur, int f) {
    static int tim;
    in[cur] = ++tim, top[cur] = f, rnk[tim] = cur;
    if (!hSon[cur]) return;
    dfs2(hSon[cur], f);
    for (auto& to : G[cur])
        if (to != hSon[cur] && to != fa[cur]) dfs2(to, to);
}
/*---------------------------------------*/
inline void request(int u, int v, int val) {
    vector<pair<int, int>> seg;
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        seg.push_back({in[top[u]], in[u]});
        u = fa[top[u]];
    }
    if (in[u] > in[v]) swap(u, v);
    seg.push_back({in[u], in[v]});
    sort(seg.begin(), seg.end());
    if (seg[0].first > 1) modify(root, 1, seg[0].first - 1, val);
    for (int i = 1; i < seg.size(); i++)
        if (seg[i - 1].second != seg[i].first)
            modify(root, seg[i - 1].second + 1, seg[i].first - 1, val);
    if (seg.back().first < n) modify(root, seg.back().second + 1, n, val);
}

signed main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs1(1, 1), dfs2(1, 1), build(root);
    for (int i = 0; i <= n; i++) G[i].clear();
    for (int i = 1; i <= m; i++) {
        int type, u, v, w;
        cin >> type;
        if (type == 0) {
            cin >> u >> v >> w, event[i] = {{u, v}, w};
            request(u, v, w);
        } else if (type == 1) {
            cin >> u;
            request(event[u].first.first, event[u].first.second, -event[u].second);
        } else
            cin >> u, ans = -1e9, ask(root, in[u]), cout << ans << "\n";
    }
    return 0;
}
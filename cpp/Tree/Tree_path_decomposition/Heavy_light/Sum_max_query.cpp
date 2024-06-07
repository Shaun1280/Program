#include <bits/stdc++.h>
//P2590 [ZJOI2008]树的统计 单点修改 链上最大值 链上求和
using namespace std;

constexpr int MAXN = 3e4 + 4;

int n, q;
array<int, MAXN> fa, depth, sz, rnk, in, top, hSon, val;
vector<int> G[MAXN];

struct SegTree {
    SegTree *lson, *rson;
    int l, r;
    int sum, max;
} *root, tree[MAXN << 1];

inline SegTree* newNode(SegTree*& root, int l, int r) {
    static int tot;
    root = &tree[tot++], root->l = l, root->r = r;
    return root;
}

inline void update(SegTree* root) {
    root->max = max(root->lson->max, root->rson->max);
    root->sum = root->lson->sum + root->rson->sum;
}

inline void build(SegTree*& root, int l = 1, int r = n) {
    newNode(root, l, r);
    if (l == r) {
        root->sum = root->max = val[rnk[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(root->lson, l, mid), build(root->rson, mid + 1, r);
    update(root);
}

inline void modify(SegTree* root, int pos, int val) {
    if (root->l == pos && root->r == pos) {
        root->max = root->sum = val;
        return;
    }
    int mid = (root->l + root->r) >> 1;
    if (pos <= mid) modify(root->lson, pos, val);
    else modify(root->rson, pos, val);
    update(root);
}

inline int askMax(SegTree* root, int l, int r) {
    if (l <= root->l && root->r <= r) return root->max;
    int mid = (root->l + root->r) >> 1, res = -2e9;
    if (l <= mid) res = max(res, askMax(root->lson, l, r));
    if (r > mid) res = max(res , askMax(root->rson, l, r));
    return res;
}

inline int askSum(SegTree* root, int l, int r) {
    if (l <= root->l && root->r <= r) return root->sum;
    int mid = (root->l + root->r) >> 1, res = 0;
    if (l <= mid) res += askSum(root->lson, l, r);
    if (r > mid) res += askSum(root->rson, l, r);
    return res;
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
    for (auto& to : G[cur]) {
        if (to != hSon[cur] && to != fa[cur]) dfs2(to, to);
    }
}
/*---------------------------------------*/
inline void change(int u, int t) { modify(root, in[u], t); }

inline void chainMax(int u, int v, int res = -2e9) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        res = max(res, askMax(root, in[top[u]], in[u]));
        u = fa[top[u]];
    }
    if (in[u] > in[v]) swap(u, v);
    res = max(res, askMax(root, in[u], in[v]));
    cout << res << "\n";
}

inline void chainSum(int u, int v, int res = 0) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        res += askSum(root, in[top[u]], in[u]);
        u = fa[top[u]];
    }
    if (in[u] > in[v]) swap(u, v);
    res += askSum(root, in[u], in[v]);
    cout << res << "\n";
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> val[i];
    dfs1(1, 1), dfs2(1, 1), build(root);
    cin >> q;
    string opt;
    while (q--) {
        int u, v;
        cin >> opt >> u >> v;
        if (opt == "QMAX") chainMax(u, v);
        else if (opt == "QSUM") chainSum(u, v);
        else change(u, v);
    }
    return 0;
}
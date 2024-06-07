#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P2633 树上静态第 k 小
using namespace std;

constexpr int MAXN = 1e5 + 5;

template <typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct SegTree {
    SegTree *lson, *rson;
    int sum;
} *root[MAXN], tree[MAXN << 6];

inline SegTree* newNode(SegTree*& root) {
    static int tot;
    return root = &tree[tot++];
}

inline void build(SegTree*& root, int L, int R) {
    newNode(root);
    if (L == R) return;
    int mid = (L + R) >> 1;
    build(root->lson, L, mid), build(root->rson, mid + 1, R);
}

inline void modify(SegTree* pre, SegTree*& root, int L, int R, int pos) {
    root = newNode(root), *root = *pre;
    if (L == pos && R == pos) {
        root->sum++;
        return;
    }
    int mid = (L + R) >> 1;
    if (pos <= mid) modify(pre->lson, root->lson, L, mid, pos);
    else modify(pre->rson, root->rson, mid + 1, R, pos);
    root->sum = root->lson->sum + root->rson->sum;
}

inline int query(SegTree* r1, SegTree* r2, SegTree* r3, SegTree* r4, int L,
                 int R, int k) {
    if (L == R) return L;
    int Lsize = r1->lson->sum + r2->lson->sum - r3->lson->sum - r4->lson->sum;
    int mid = (L + R) >> 1;
    if (Lsize >= k) return query(r1->lson, r2->lson, r3->lson, r4->lson, L, mid, k);
    return query(r1->rson, r2->rson, r3->rson, r4->rson, mid + 1, R, k - Lsize);
}

int n, m, cnt, lastans;
vector<int> G[MAXN];
array<int, MAXN> val, fa, depth, top, rnk, sz, hSon, in;

unordered_map<int, int> mp, from;
inline void discrete() {
    vector<int> vec;
    for (int i = 1; i <= n; i++) vec.push_back(val[i]);
    sort(vec.begin(), vec.end());
    cnt = unique(vec.begin(), vec.end()) - vec.begin();
    for (int i = 0; i < cnt; i++) 
        mp[vec[i]] = i + 1, from[i + 1] = vec[i];
}

inline void dfs1(int cur, int f) {
    sz[cur] = 1, depth[cur] = depth[f] + 1, fa[cur] = f;
    root[cur] = root[f];
    modify(root[cur], root[cur], 1, cnt, mp[val[cur]]);
    for (int i = 0; i < G[cur].size(); i++) {
        int to = G[cur][i];
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
    for (int i = 0; i < G[cur].size(); i++) {
        int to = G[cur][i];
        if (to == hSon[cur] || to == fa[cur]) continue;
        dfs2(to, to);
    }
}

inline int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return in[u] < in[v] ? u : v;
}

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++) read(val[i]);
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        G[u].push_back(v), G[v].push_back(u);
    }
    discrete();
    build(root[0], 1, cnt);
    dfs1(1, 0), dfs2(1, 1);
    while (m--) {
        int u, v, k;
        read(u), read(v), read(k);
        u ^= lastans;
        int lca = LCA(u, v), fLca = fa[lca];
        printf("%d\n", lastans = from[query(root[u], root[v], root[lca], root[fLca], 1, cnt, k)]);
    }
    return 0;
}
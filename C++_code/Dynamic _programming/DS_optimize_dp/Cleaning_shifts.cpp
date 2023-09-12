#include <bits/stdc++.h>
#define int long long
//P4644 [USACO05DEC]Cleaning Shifts S 线段树优化dp
using namespace std;
//https://www.luogu.com.cn/problem/P4644
constexpr int MAXN = 1e5 + 5;

template<typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct SegTree {
    SegTree * lson, *rson;
    int l, r, min = 1e16;
} *root, tree[MAXN << 2];

struct Cow {
    int l, r, cost;
    friend inline bool operator<(const Cow &lhs, const Cow &rhs) {
        return lhs.r == rhs.r ? lhs.l < rhs.l : lhs.r < rhs.r;
    }
} cow[MAXN];

int n, m, e;

inline SegTree *newNode(SegTree*& root) {
    static int tot;
    return root ? root : root = &tree[tot++];
}

inline void update(SegTree *root) {
    root->min = min(root->lson->min, root->rson->min);
}

inline void build(SegTree *root, int l, int r) {
    root->l = l, root->r = r;
    if (l == r) {
        if (l == m - 1) root->min = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(newNode(root->lson), l, mid);
    build(newNode(root->rson), mid + 1, r);
    update(root);
}

inline void modify(SegTree* root, int pos, int val) {
    if (pos == root->l && root->r == pos) {
        root->min = val;
        return;
    }
    int mid = (root->l + root->r) >> 1;
    if (pos <= mid) modify(root->lson, pos, val);
    else modify(root->rson, pos, val);
    update(root);
}

inline int query(SegTree* root, int l, int r) {
    if (l <= root->l && root->r <= r) {
        return root->min;
    }
    int mid = (root->l + root->r) >> 1, res = 1e16;
    if (l <= mid) res = min(res, query(root->lson, l, r));
    if (r > mid) res = min(res, query(root->rson, l, r));
    return res;
}
//dp[x] 表示覆盖[m, x]的最小代价 单点修改 区间最值
signed main () {
    read(n), read(m), read(e), m++, e++;
    for (int i = 1; i <= n; i++) {
        read(cow[i].l), read(cow[i].r), read(cow[i].cost);
        cow[i].l++, cow[i].r++;
    }
    sort(cow + 1, cow + n + 1);
    build(newNode(root), m - 1, e);
    for (int i = 1; i <= n; i++) {
        int mi = query(root, max(m - 1, cow[i].l - 1), min(e, cow[i].r - 1));
        if (mi == 1e16) continue; //!
        modify(root, min(e, cow[i].r), mi + cow[i].cost);
    }
    int ans = query(root, e, e);
    printf("%lld\n", ans == 1e16 ? -1 : ans);
    return 0;
}
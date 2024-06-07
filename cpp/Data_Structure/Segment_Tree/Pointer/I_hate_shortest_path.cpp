#include <bits/stdc++.h>
#define int long long
using namespace std;
//https://atcoder.jp/contests/abc177 F - I hate Shortest Path Problem
constexpr int MAXN = 2e5 + 5;
//线段树维护等差数列 + 区间最小值 + 优化dp
template<typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct SegTree {
    SegTree *lson, *rson;
    int l, r;
    int min, Lval; //min为区间最小值，Lval为节点最左端l的值
    int tag1, tag2; //tag1为区间加标记，tag2为公差标记
} *root, tree[MAXN << 1];
int h, w, a[MAXN], b[MAXN], ans[MAXN];

inline SegTree* newNode(SegTree*& root) {
    static int tot;
    return root = &tree[tot++];
}

inline void update(SegTree* root) {
    root->min = min(root->lson->min, root->rson->min);
}

inline void build(SegTree* root, int l, int r) {
    root->l = l, root->r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(newNode(root->lson), l, mid);
    build(newNode(root->rson), mid + 1, r);
    update(root);
}

inline void pushTag(SegTree* root) {
    if (root->tag1) {
        root->lson->tag1 += root->tag1, root->rson->tag1 += root->tag1;
        root->lson->Lval += root->tag1, root->rson->Lval += root->tag1;
        root->lson->min += root->tag1, root->rson->min += root->tag1;
    }
    if (root->tag2) {
        root->lson->tag2 = root->tag2, root->rson->tag2 = root->tag2;
        root->lson->min = root->lson->Lval
            = root->Lval + (root->lson->l - root->l) * root->tag2;
        root->rson->min = root->rson->Lval
             = root->Lval + (root->rson->l - root->l) * root->tag2;
    }
    root->tag1 = root->tag2 = 0;
}

inline void modify(SegTree* root, int l, int r, int val, int type) {
    if (l <= root->l && root->r <= r) {
        if (type == 1) //区间加1
            root->min += val, root->Lval += val, root->tag1 += val;
        else { //区间等差数列 min Lval赋最左端的值
            root->Lval = root->min = root->l - l + 1 + val;
            root->tag2 = 1; //公差为 1 的等差数列
        }
        return;
    }
    pushTag(root);
    int mid = (root->l + root->r) >> 1;
    if (l <= mid) modify(root->lson, l, r, val, type);
    if (r > mid) modify(root->rson, l, r, val, type);
    update(root);
}

inline int query(SegTree* root, int l, int r) { //查询最小值
    if (l <= root->l && root->r <= r)
        return root->min;
    pushTag(root);
    int mid = (root->l + root->r) >> 1, res = 1e18;
    if (l <= mid) res = min(res, query(root->lson, l, r));
    if (r > mid) res = min(res, query(root->rson, l, r));
    return res;
}

signed main() {
    read(h), read(w);
    for (int i = 1; i <= h; i++) read(a[i]), read(b[i]);
    build(newNode(root), 1, w);
    for (int i = 1; i <= h; i++) {
        modify(root, a[i], b[i], 1e12, 1);
        if (a[i] > 1) modify(root, 1, a[i] - 1, 1, 1);
        if (b[i] < w) modify(root, b[i] + 1, w, 1, 1);
        int mi = a[i] == 1 ? 1e12 : query(root, a[i] - 1, a[i] - 1);
        modify(root, a[i], b[i], mi, 2);
        ans[i] = query(root, 1, w);
    }
    for (int i = 1; i <= h; i++) printf("%lld\n", ans[i] >= 1e12 ? -1 : ans[i]);
    return 0;
}
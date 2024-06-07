#include <bits/stdc++.h>
//https://codeforces.ml/contest/1401/problem/F
using namespace std;

constexpr int MAXN = 3e5 + 5, MOD = 1e9 + 7;

template<typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

int bit, n, q, a[MAXN], tag[19], tot;

struct SegTree {
    SegTree* lson, *rson;
    int tag, depth;
    long long sum;
} *root, tree[MAXN << 1];

inline void update(SegTree* root) {
    root->sum = root->lson->sum + root->rson->sum;
}

inline void build(SegTree*& root, int L, int R, int depth) {
    root = &tree[tot++], root->depth = depth;
    if (L == R) { root->sum = a[L]; return; }
    int mid = (L + R) >> 1;
    build(root->lson, L, mid, depth + 1);
    build(root->rson, mid + 1, R, depth + 1);
    update(root);
}

inline void checkTag(SegTree* root) {
    if (root->tag != tag[root->depth]) {
        root->tag = tag[root->depth];
        swap(root->lson, root->rson);
    }
}

inline void modify(SegTree* root, int pos, int val, int L = 1, int R = n) {
    if (L == pos && R == pos) {
        root->sum = val;
        return;
    }
    checkTag(root);
    int mid = (L + R) >> 1;
    if (pos <= mid) modify(root->lson, pos, val, L, mid);
    else modify(root->rson, pos, val, mid + 1, R);
    update(root);
}

inline long long query(SegTree* root, int l, int r, int L = 1, int R = n) {
    if (l <= L && R <= r) return root->sum;
    checkTag(root);
    int mid = (L + R) >> 1;
    long long res = 0;
    if (l <= mid) res += query(root->lson, l, r, L, mid);
    if (r > mid) res += query(root->rson, l, r, mid + 1, R);
    update(root);
    return res;
}

int main() {
    read(bit), read(q), n = pow(2, bit);
    for (int i = 1; i <= n; i++) read(a[i]);
    build(root, 1, n, 0);
    while (q--) {
        int opt, x, k, l, r;
        read(opt);
        if (opt == 1) read(x), read(k), modify(root, x, k);
        else if (opt == 2) {
            read(k);
            for (int i = bit - k; i <= bit; i++) tag[i] ^= 1;
        } else if (opt == 3) read(k), tag[bit - k - 1] ^= 1;
        else read(l), read(r), printf("%lld\n", query(root, l, r));
    }
    return 0;
}
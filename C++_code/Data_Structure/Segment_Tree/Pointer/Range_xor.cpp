#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF242E
using namespace std;
//区间异或 求和
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
    int l, r, tag;
    long long sum;
} *root[20], tree[80 * MAXN];
int n, m, num[MAXN], bit;

inline SegTree* newNode(SegTree*& root) {
    static int tot;
    return root ? root : root = &tree[tot++];
}

inline void update(SegTree* root) {
    root->sum = root->lson->sum + root->rson->sum;
}

inline void pushTag(SegTree* root) {
    if (!root->tag) return;
    root->lson->tag ^= root->tag;
    root->rson->tag ^= root->tag;
    root->lson->sum = root->lson->r - root->lson->l + 1 - root->lson->sum;
    root->rson->sum = root->rson->r - root->rson->l + 1 - root->rson->sum;
    root->tag = 0;
}

inline void build(SegTree* root, const int& l, const int& r) {
    root->l = l, root->r = r;
    if (l == r) {
        root->sum = ((num[l] >> bit) & 1);
        return;
    }
    int mid = l + r >> 1;
    build(newNode(root->lson), l, mid);
    build(newNode(root->rson), mid + 1, r);
    update(root);
}

inline void modify(SegTree*& root, const int& l, const int& r) {
    if (l <= root->l && root->r <= r) {
        root->sum = root->r - root->l + 1 - root->sum;
        root->tag ^= 1;
        return;
    }
    pushTag(root);
    int mid = root->l + root->r >> 1;
    if (l <= mid) modify(root->lson, l, r);
    if (r > mid) modify(root->rson, l, r);
    update(root);
}

inline long long query(SegTree*& root, const int& l, const int& r) {
    if (l <= root->l && root->r <= r) {
        return root->sum;
    }
    pushTag(root);
    int mid = root->l + root->r >> 1;
    long long res = 0;
    if (l <= mid) res += query(root->lson, l, r);
    if (r > mid) res += query(root->rson, l, r);
    return res;
}

int main () {
    read(n);
    for (int i = 1; i <= n; i++) read(num[i]);
    for (bit = 0; bit < 20; bit++) //20颗线段树
        build(newNode(root[bit]), 1, n);
    read(m);
    while (m--) {
        int opt, l, r, x;
        read(opt), read(l), read(r);
        if (opt == 1) {
            long long ans = 0;
            for (bit = 0; bit < 20; bit++)
                ans += (1LL << bit) * query(root[bit], l, r);
            printf("%lld\n", ans);
            //printf("%I64d\n", ans);
        }
        else if (opt == 2) {
            read(x);
            for (bit = 0; bit < 20; bit++) {
                if ((x & (1 << bit)) == 0) continue; //do not range not
                modify(root[bit], l, r); //range not
            }
        }
    }
    return 0;
}
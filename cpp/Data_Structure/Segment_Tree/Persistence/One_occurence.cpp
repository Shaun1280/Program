#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF1000F 区间内只出现一次的数
using namespace std;

constexpr int MAXN = 5e5 + 5;

template<typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct SegTree {
    SegTree * lson, *rson;
    int min = 1e9;
} *root[MAXN], tree[MAXN * 60];
int n, m, pre[MAXN], arr[MAXN];

inline SegTree* newNode (SegTree*& root) {
    static int tot;
    return root = &tree[tot++];
}

inline void build(SegTree* root, int L, int R) {
    if (L == R) return;
    int mid = (L + R) >> 1;
    build(newNode(root->lson), L, mid);
    build(newNode(root->rson), mid + 1, R);
}

inline void modify (SegTree* pre, SegTree*& root, int L, int R, int pos, int val) {
    root = newNode(root), *root = *pre;
    if (L == pos && R == pos) {
        root->min = val;
        return;
    }
    int mid = (L + R) >> 1;
    if (pos <= mid) modify(pre->lson, root->lson, L, mid, pos, val);
    else modify(pre->rson, root->rson, mid + 1, R, pos, val);
    root->min = min(root->lson->min, root->rson->min);
}

inline int query(SegTree* root, int L, int R, int qL, int qR) {
    if (L > qR || R < qL || root->min >= qL) return 0;
    if (L == R) return L;
    int mid = (L + R) >> 1;
    int tmp = query(root->lson, L, mid, qL, qR);
    if (!tmp) return query(root->rson, mid + 1, R, qL, qR);
    return tmp;
}

int main() {
    read(n);
    build(newNode(root[0]), 1, n); //按下标建立可持久化线段树
    for (int i = 1; i <= n; i++) {
        read(arr[i]);
        root[i] = root[i - 1];
        if (pre[arr[i]]) modify(root[i], root[i], 1, n, pre[arr[i]], 1e9);
        //上一个位置设为1e9
        modify(root[i], root[i], 1, n, i, pre[arr[i]]);
        pre[arr[i]] = i;
    }
    read(m);
    while (m--) {
        int l, r;
        read(l), read(r);
        printf("%d\n", arr[query(root[r], 1, n, l, r)]);
    }
    return 0;
}
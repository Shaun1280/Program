#include <bits/stdc++.h>
#define int long long
//https://www.luogu.com.cn/problem/UVA12436
using namespace std;
//区间加等差数列 区间求和 区间赋值
constexpr int MAXN = 3e5 + 5;

template <typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct SegTree {
    SegTree *lson, *rson;
    int l, r;
    int sum, Lval; // sum为区间和，Lval为增加的等差数列首项标记
    int tag1 = 1e18, tag2;  // tag1为区间赋值标记，tag2为公差标记
} * root, tree[MAXN << 1];

inline SegTree* newNode(SegTree*& root) {
    static int tot;
    return root = &tree[tot++];
}

inline void update(SegTree* root) {
    root->sum = root->lson->sum + root->rson->sum;
}

inline int size(SegTree* root) { return root->r - root->l + 1; }
/*@param Lval 首项 @param d 公差 @param len 项数*/
inline int sum(int Lval, int d, int len) {
    return Lval * len + d * len * (len - 1) / 2;
}

inline void build(SegTree* root, int l, int r) {
    root->l = l, root->r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(newNode(root->lson), l, mid);
    build(newNode(root->rson), mid + 1, r);
}

inline void pushTag(SegTree* root) {
    if (root->tag1 != 1e18) {  //区间修改
        root->lson->tag1 = root->tag1, root->rson->tag1 = root->tag1;
        //区间修改后首项 公差为 0
        root->lson->Lval = root->rson->Lval = 0;
        root->lson->tag2 = root->rson->tag2 = 0;

        root->lson->sum = root->tag1 * size(root->lson);
        root->rson->sum = root->tag1 * size(root->rson);
        root->tag1 = 1e18;
    }
    if (root->tag2 || root->Lval) {  //区间等差数列
        root->lson->tag2 += root->tag2, root->rson->tag2 += root->tag2;

        root->lson->Lval += root->Lval;
        root->rson->Lval += root->Lval + root->tag2 * size(root->lson);
        //注意是从父亲root->Lval累加下来 新增的等差数列求和
        root->lson->sum += sum(root->Lval, root->tag2, size(root->lson));
        root->rson->sum += sum(root->Lval + root->tag2 * size(root->lson),
                               root->tag2, size(root->rson));
        root->tag2 = root->Lval = 0;  //两个都要清零
    }
}

inline void modify(SegTree* root, int l, int r, int val, int type) {
    if (l <= root->l && root->r <= r) {
        if (type == 1) {  //区间赋值
            root->sum = val * size(root);
            root->tag1 = val;
            root->Lval = root->tag2 = 0;  //!
        } else if (type == 2) {           //区间增加等差数列 公差 1
            root->Lval += root->l - l + val;
            root->tag2++;
            root->sum += sum(root->l - l + val, 1, size(root));
        } else {  //区间增加等差数列 公差 -1
            root->Lval += l - root->l + val;
            root->tag2--;
            root->sum += sum(l - root->l + val, -1, size(root));
        }
        return;
    }
    pushTag(root);
    int mid = (root->l + root->r) >> 1;
    if (l <= mid) modify(root->lson, l, r, val, type);
    if (r > mid) modify(root->rson, l, r, val, type);
    update(root);
}

inline int query(SegTree* root, int l, int r) {  //查询最小值
    if (l <= root->l && root->r <= r) return root->sum;
    pushTag(root);
    int mid = (root->l + root->r) >> 1, res = 0;
    if (l <= mid) res += query(root->lson, l, r);
    if (r > mid) res += query(root->rson, l, r);
    return res;
}

signed main() {
    int n;
    read(n);
    build(newNode(root), 1, 250000);
    char opt[2];
    for (int i = 1, l, r, x; i <= n; i++) {
        scanf("%s", opt), read(l), read(r);
        if (opt[0] == 'A') modify(root, l, r, 1, 2);
        else if (opt[0] == 'B') modify(root, l, r, r - l + 1, 3);
        else if (opt[0] == 'C') read(x), modify(root, l, r, x, 1);
        else printf("%lld\n", query(root, l, r));
    }
    return 0;
}
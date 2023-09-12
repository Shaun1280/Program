#include <bits/stdc++.h>
#define int long long
//New Passenger Trams https://codeforces.ml/contest/1379/problem/D
using namespace std;

constexpr int MAXN = 1e5 + 5;

template <typename T>
inline void read(T& x, T f = 1, char ch = getchar()) {
    x = 0;
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
//dynamic segment tree
struct SegTree {
    SegTree * lson, *rson;
    int l, r, id, add = 0, min = 0;
} *root, tree[MAXN * 64];
#define Lson root->lson
#define Rson root->rson

inline SegTree* newNode(SegTree*& root, int l, int r) {
    static int tot;
    if (root) return root;
    root = &tree[tot++], root->l = l, root->r = r, root->id = l;
    return root;
}

inline void update(SegTree* root) { //更新
    if (Lson->min <= Rson->min)
        root->min = Lson->min, root->id = Lson->id;
    else root->min = Rson->min, root->id = Rson->id;
}

inline void pushTag(SegTree* root) { //下放标记
    if (Lson) Lson->min += root->add, Lson->add += root->add;
    if (Rson) Rson->min += root->add, Rson->add += root->add;
    root->add = 0;
}

inline void insert(SegTree* root, int l, int r) { //区间增值 动态开点
    if (root->l == l && root->r == r) {
        root->min++, root->add++;
        return;
    }
    int mid = (root->l + root->r) >> 1;
    newNode(Lson, root->l, mid), newNode(Rson, mid + 1, root->r);//开辟左右儿子
    pushTag(root);
    if (r <= mid) insert(Lson, l, r);
    else if (l > mid) insert(Rson, l, r);
    else insert(Lson, l, mid), insert(Rson, mid + 1, r);
    update(root);
}

int n, H, M, k, h[MAXN], m[MAXN];

signed main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    read(n), read(H), read(M), read(k);
    if (k == 1) cout << 0 << " " << 0, exit(0);
    newNode(root, 0, M / 2 - 1);
    for (int i = 1; i <= n; i++) {
        read(h[i]), read(m[i]);

        if (m[i] + 1 <= M / 2 - 1)
            insert(root, max(k - 1, m[i] + 1), min(M / 2, m[i] + k) - 1);
        if (m[i] + k - 1 - M / 2 >= k - 1 && m[i] + 1 - M / 2 <= M / 2 - 1)
            insert(root, max(k - 1, m[i] + 1 - M / 2), min(M / 2, m[i] + k - M / 2) - 1);

        if (m[i] + k - 1 - M >= 0)
            insert(root, 0, min(k - 2, m[i] + k - 1 - M));
        if (m[i] + 1 <= k - 2) 
            insert(root, m[i] + 1, k - 2);
        if (m[i] + k - 1 - M / 2 >= 0 && m[i] + 1 - M / 2 <= k - 2)
            insert(root, max(0LL, m[i] + 1 - M / 2), min(k - 2, m[i] + k - 1 - M / 2));
    }
    cout << root->min << " " << root->id << "\n";
    int t = root->id;
    for (int i = 1; i <= n; i++) {
        if (t >= k - 1) {
            if (t - k + 1 <= m[i] && m[i] <= t - 1)
                cout << i << " ";
            else if (t - k + 1 + M / 2 <= m[i] && m[i] <= t - 1 + M / 2)
                cout << i << " ";
        } else {
            if (t >= 1 && m[i] <= t - 1)
                cout << i << " ";
            else if (t - k + 1 + M <= m[i] && m[i] <= M - 1)
                cout << i << " ";
            else if (t - k + 1 + M / 2 <= m[i] && m[i] <= t - 1 + M / 2)
                cout << i << " ";
        }
    }
    return 0;
}
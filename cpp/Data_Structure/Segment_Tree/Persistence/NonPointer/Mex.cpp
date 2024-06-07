#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P4137
using namespace std;
//P4137 Rmq Problem / mex
constexpr int MAXN = 2e5 + 5;

struct SegTree {
    int lson, rson, minPos; //minPos为区间内val最后一次出现位置的最小值
} tree[MAXN * 32];
int root[MAXN], n, m;

inline int newNode (int& root) {
    static int tot;
    return root = ++tot;
}

#define Lson tree[root].lson
#define Rson tree[root].rson
inline void modify (int pre, int root, int L, int R, int val, int pos) {
    tree[root] = tree[pre];
    if (L == val && R == val) {
        tree[root].minPos = pos;
        return;
    }
    int mid = (L + R) >> 1;
    if (val <= mid) modify(tree[pre].lson, newNode(Lson), L, mid, val, pos);
    else modify(tree[pre].rson, newNode(Rson), mid + 1, R, val, pos);
    tree[root].minPos = min(tree[Lson].minPos, tree[Rson].minPos);
}

inline int query(int root, int L, int R, int pos) {
    if (L == R) return L;
    int mid = (L + R) >> 1; //先查询左儿子
    if (tree[Lson].minPos < pos) return query(Lson, L, mid, pos); //最小值小于l
    else return query(Rson, mid + 1, R, pos);
}

int main() {
    std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1, tmp; i <= n; i++) {
        cin >> tmp;
        if (tmp > n) root[i] = root[i - 1]; //结果一定 <= n
        else {
            modify(root[i - 1], newNode(root[i]), 0, n, tmp, i);
        }
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(root[r], 0, n, l) << "\n";
    }
    return 0;
}
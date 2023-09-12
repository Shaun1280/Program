#include <bits/stdc++.h>
// https://ac.nowcoder.com/acm/contest/11258/K
// 每次操作选一个区间 + 1 或 -1 % k 询问最少操作使区间 [l, r] 全部变为 0
// 二分 + 可持久化值域线段树
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7, lim = (1 << 30);

#define ls(x) tree[x].lson
#define rs(x) tree[x].rson
struct SegT {
    int lson, rson;
    long long sum;
    int sz;
} tree[MAXN * 80];
int n, q, tot, a[MAXN], d[MAXN];
long long sumd[MAXN];
int negr[MAXN], posr[MAXN], negc[MAXN], posc[MAXN];

int newN(int& root) { return root = ++tot; }

void modify(int root, int pre, int l, int r, int x) {
    tree[root] = tree[pre];
    tree[root].sum += x, tree[root].sz++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) modify(newN(ls(root)), ls(pre), l, mid, x);
    else modify(newN(rs(root)), rs(pre), mid + 1, r, x);
}

long long query(int root, int pre, int l, int r, int k) {
    if (k == 0) return 0;
    if (l == r) {
        return 1LL * k * (tree[root].sum - tree[pre].sum) / (tree[root].sz - tree[pre].sz);
    }
    int mid = (l + r) >> 1;
    if (k <= tree[rs(root)].sz - tree[rs(pre)].sz) return query(rs(root), rs(pre), mid + 1, r, k);
    else return tree[rs(root)].sum - tree[rs(pre)].sum + query(ls(root), ls(pre), l, mid, k - (tree[rs(root)].sz - tree[rs(pre)].sz));
}

long long ask(int L, int R, int k) {
    int r1, r2;
    modify(newN(r2), posr[R], 0, lim, a[L]); // a[L] - 0
    modify(newN(r1), negr[R], 0, lim, a[R]); // 0 -a[R]
    int l = 1, r = min(tree[r2].sz - tree[posr[L]].sz, tree[r1].sz - tree[negr[L]].sz), res = 0;
    while (l <= r) { // 二分 导数
        int mid = (l + r) >> 1;
        long long s1= 1LL * k * mid - query(r2, posr[L], 0, lim, mid) * 2; // 主席树前 k 大，可重
        long long s2= 1LL * k * mid - query(r1, negr[L], 0, lim, mid) * 2; // delta = k - 2|x| = k - 2 * d
        long long s11 = 1LL * k * (mid - 1) - query(r2, posr[L], 0, lim, mid - 1) * 2;
        long long s22 = 1LL * k * (mid - 1) - query(r1, negr[L], 0, lim, mid - 1) * 2;
        if (s1 + s2 <= s11 + s22) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    long long tmp = 2LL * k * res - query(r2, posr[L], 0, lim, res) * 2 - query(r1, negr[L], 0, lim, res) * 2;
    return (sumd[R] - sumd[L] + a[L] + a[R] + tmp) / 2;
}

int main() {
    boost;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        d[i] = abs(a[i] - a[i - 1]);
        if (a[i] > a[i - 1]) {
            modify(newN(posr[i]), posr[i - 1], 0, lim, d[i]);
            posc[i]++, negr[i] = negr[i - 1];
        } else {
            modify(newN(negr[i]), negr[i - 1], 0, lim, d[i]);
            negc[i]++, posr[i] = posr[i - 1];
        }
        sumd[i] = sumd[i - 1] + d[i]; // 不模 k，答案为 (Σ|di|) / 2 for i in [1, n + 1]
    }
    for (int i = 1, l, r, k; i <= q; i++) {
        cin >> l >> r >> k;
        if (l == r) {
            cout << min(a[l], k - a[l]) << "\n";
            continue;
        }
        cout << ask(l, r, k) << "\n";
    }
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
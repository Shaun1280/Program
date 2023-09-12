#include <bits/stdc++.h>
// https://ac.nowcoder.com/acm/contest/11258/B
using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) { cout << endl; }

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << " ";
    err(++it, args...);
}

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 3e5 + 5, MOD = 1e9 + 7;

#define ls(x) (x << 1)
#define rs(x) ((x << 1) | 1)
#define mid(x) ((tree[x].l + tree[x].r) >> 1)
struct SegT {
    int l, r;
    pair<int, bool> max; // 最大的 a 以及相应 b
    int r_num;
    bool tag;
} tree[MAXN << 2];
int a[MAXN], n, q;
bool b[MAXN];

void pushdown(int root) {
    if (tree[root].tag) {
        tree[ls(root)].max.second ^= tree[root].tag;
        tree[rs(root)].max.second ^= tree[root].tag;
        tree[ls(root)].tag ^= tree[root].tag;
        tree[rs(root)].tag ^= tree[root].tag;
        tree[root].tag = 0;
    }
}

int calc(int root, const pair<int, bool>& mx) { // 当前最大值为 a = mx.fisrt，对应的 b 为 mx.second，遍历区间 [l, r] 的答案
    if (tree[root].l == tree[root].r) {
        return tree[root].max.first >= mx.first && tree[root].max.second != mx.second;
    }
    pushdown(root);
    if (tree[ls(root)].max.first >= mx.first) // 优先左子树
        return calc(ls(root), mx) + tree[root].r_num;
    else return calc(rs(root), mx); // 在右子树找最大 a
}

pair<int, bool> pairMax(const pair<int, bool>& lhs, const pair<int, bool>& rhs) {
    return lhs.first > rhs.first ? lhs : rhs; // 多个相等取最右边
}

void update(int root) {
    tree[root].max = pairMax(tree[ls(root)].max, tree[rs(root)].max);
    tree[root].r_num = calc(rs(root), tree[ls(root)].max);
}

void build(int root, int l, int r) {
    tree[root].l = l, tree[root].r = r;
    if (l == r) {
        tree[root].max = {a[l], b[l]};
        return;
    }
    int mid = mid(root);
    build(ls(root), l, mid), build(rs(root), mid + 1, r);
    update(root);
}

void modify_a(int root, int x, int val) {
    if (tree[root].l == tree[root].r) {
        tree[root].max.first = val;
        return;
    }
    pushdown(root);
    int mid = mid(root);
    if (x <= mid) modify_a(ls(root), x, val);
    else modify_a(rs(root), x, val);
    update(root);
}

void modify_b(int root, int l, int r) {
    if (l <= tree[root].l && tree[root].r <= r) {
        tree[root].max.second ^= 1;
        tree[root].tag ^= 1;
        return;
    }
    pushdown(root);
    int mid = mid(root);
    if (l <= mid) modify_b(ls(root), l, r);
    if (r > mid) modify_b(rs(root), l, r);
    update(root);
}

vector<int> roots;
void divide(int root, int l, int r) {
    if (l <= tree[root].l && tree[root].r <= r) {
        roots.push_back(root);
        return;
    }
    pushdown(root);
    int mid = mid(root);
    if (l <= mid) divide(ls(root), l, r);
    if (r > mid) divide(rs(root), l, r);
    update(root);
}

pair<int, bool> qMax(int root, int x) {
    if (tree[root].l == tree[root].r) return tree[root].max;
    pushdown(root);
    int mid = mid(root);
    if (x <= mid) return qMax(ls(root), x);
    else return qMax(rs(root), x);
}

int query(int l, int r, int res = 0) {
    if (l == r) return 0;
    roots.clear();
    pair<int, bool> mx = qMax(1, l);
    divide(1, l + 1, r);
    for (auto& i : roots) {
        res += calc(i, mx);
        mx = pairMax(mx, tree[i].max);
    }
    return res;
}

int main() {
    // freopen("test.in", "r", stdin);
    boost;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    build(1, 1, n);
    cin >> q;
    while (q--) {
        int opt, t1, t2;
        cin >> opt >> t1 >> t2;
        if (opt == 1) modify_a(1, t1, t2);
        else if (opt == 2) modify_b(1, t1, t2);
        else cout << query(t1, t2) << "\n";
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
#include <bits/stdc++.h>

using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define int long long

constexpr int MAXN = 200005, MOD = 1e9 + 7;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

#define ls(x) tree[x].lson
#define rs(x) tree[x].rson
struct SegTree {
    int l, r;
    int lson, rson;
    int sum = 1;
    int tag = 1;
} tree[MAXN << 1];

int root, tot;
int newNode(int& x) {
    x = ++tot;
    return x;
}

void update(int x) { tree[x].sum = (tree[ls(x)].sum + tree[rs(x)].sum) % MOD; }

map<int, int> mpx, mpy;
vector<int> vecx, vecy;
void build(int x, int l, int r) {
    tree[x].l = l, tree[x].r = r;
    if (l == r) {
        tree[x].sum = l ? vecx[l] - vecx[l - 1] : vecx[l], tree[x].tag = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(newNode(ls(x)), l, mid);
    build(newNode(rs(x)), mid + 1, r);
    update(x);
}

void pushdown(int x) {
    if (tree[x].tag == 1) return;
    tree[ls(x)].tag = tree[ls(x)].tag * tree[x].tag % MOD;
    tree[rs(x)].tag = tree[rs(x)].tag * tree[x].tag % MOD;
    tree[ls(x)].sum = tree[ls(x)].sum * tree[x].tag % MOD;
    tree[rs(x)].sum = tree[rs(x)].sum * tree[x].tag % MOD;
    tree[x].tag = 1;
}

void modify(int x, int ql, int qr, int val) {
    if (ql <= tree[x].l && tree[x].r <= qr) {
        tree[x].sum = tree[x].sum * val % MOD;
        tree[x].tag = tree[x].tag * val % MOD;
        return;
    }
    pushdown(x);
    int mid = (tree[x].l + tree[x].r) >> 1;
    if (ql <= mid) modify(ls(x), ql, qr, val);
    if (qr > mid) modify(rs(x), ql, qr, val);
    update(x);
}

int n, X[MAXN], Y[MAXN], p[MAXN];

void discrete(vector<int>& vec, int& cnt, map<int, int>& mp) {
    sort(vec.begin(), vec.end());
    cnt = unique(vec.begin(), vec.end()) - vec.begin();
    for (int i = 0; i < cnt; i++) mp[vec[i]] = i;
}

void work(int ncase) {
    cin >> n;
    tot = 0, mpx.clear(), mpy.clear();
    vecx.clear(), vecy.clear();

    int cntx, cnty;
    int mx(1), my(1);
    
    for (int i = 1, x, y, a, b; i <= n; i++) {
        cin >> x >> y >> a >> b;
        mx = max(mx, x), my = max(my, y);
        vecx.push_back(x), vecy.push_back(y);
        int P = (MOD + 1 - a * qpow(b, MOD - 2) % MOD) % MOD;
        X[i] = x, Y[i] = y, p[i] = P;
    }
    discrete(vecx, cntx, mpx);
    discrete(vecy, cnty, mpy);
    build(newNode(root), 0, cntx - 1);

    vector<pair<int, int>> vecY[cnty];
    for (int i = 1; i <= n; i++)
        vecY[mpy[Y[i]]].push_back({mpx[X[i]], p[i]});

    int ans = mx * my % MOD;
    for (int i = cnty - 1; i >= 0; i--) { // for every discrete y
        int cury = vecy[i], prey = i ? vecy[i - 1] : 0;
        int ty = cury - prey;
        for (auto& pi : vecY[i]) {
            modify(root, 0, pi.first, pi.second);
        }
        ans = (ans - tree[root].sum * ty % MOD) % MOD;
        ans = (ans + MOD) % MOD;
    }
    cout << ans << "\n";

    for (int i = 0; i <= tot; i++) tree[i].l = tree[i].r = tree[i].lson = tree[i].rson = 0, tree[i].sum = tree[i].tag = 1;
}

signed main() {
    boost;
    int testcase = 1;
    cin >> testcase;
    for (int i = 1; i <= testcase; i++) work(i);
    return 0;
}
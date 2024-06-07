#include <bits/stdc++.h>

using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e5 + 5, MOD = 1e9 + 7;

struct Cartesian {
    void build(vector<int>& a) {
        stk.resize(a.size()), lson.resize(a.size()), rson.resize(a.size());
        for (int i = 1; i < a.size(); i++) { // <= 大根堆 
            while (tp && a[stk[tp]] <= a[i]) lson[i] = stk[tp--];
            rson[stk[tp]] = i;
            stk[++tp] = i;
        }
        root = stk[1];
        dfs1(root, root), dfs2(root, root);
    }

    void dfs1(int cur, int f) {
        //error(a[cur], a[lson[cur]], a[rson[cur]]);
        sz[cur] = 1, fa[cur] = f, depth[cur] = depth[f] + 1;
        for (int i = 0; i < 2; i++) {
            int to = (i ? rson[cur] : lson[cur]);
            if (!to) continue;
            dfs1(to, cur);
            sz[cur] += sz[to];
            if (!hson[cur] || sz[to] > sz[hson[cur]]) hson[cur] = to;
        }
    }

    void dfs2(int cur, int f) {
        in[cur] = ++tim, top[cur] = f;
        if (!hson[cur]) return;
        dfs2(hson[cur], f);  //优先重链
        for (int i = 0; i < 2; i++) {
            int to = i ? rson[cur] : lson[cur];
            if (!to) continue;
            if (to != hson[cur] && to != fa[cur]) dfs2(to, to);
        }
    }

    int query(int l, int r) {
        while (top[l] != top[r]) {
            if (depth[top[l]] < depth[top[r]]) swap(l, r);
            l = fa[top[l]];
        }
        return in[l] < in[r] ? l : r;
    }

    int root = 0, tp = 0, tim = 0;
    vector<int> stk, lson, rson;
    array<int, MAXN> sz, hson, depth, top, fa, in;
} T;

int n, m, s;
vector<int> a;

int main() {
    boost;
    cin >> n >> m;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    T.build(a);
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        cout << a[T.query(l, r)] << "\n";
    }
    return 0;
}
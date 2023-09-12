#include <bits/stdc++.h>

// https://ac.nowcoder.com/acm/contest/11258/F 牛客多校第七场
// 可持久化线段树 dfs序 dp

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

int tc, n, L[MAXN];
vector<int> g[MAXN], g2[MAXN];

namespace Solution {
    #define ls(x) tree[x].lson
    #define rs(x) tree[x].rson

    int tim, tot, root[MAXN], ans(1), depth[MAXN], sz[MAXN], dp[MAXN];

    struct SegT {
        int lson, rson;
        int max, tag;
    } tree[MAXN * 32];
    
    int newNd(int& root) {return root = ++tot;}

    void build(int root, int l, int r) {
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(newNd(ls(root)), l, mid);
        build(newNd(rs(root)), mid + 1, r);
    }
    
    void modify(int root, int pre, int l, int r, int ql, int qr, int tag) {
        tree[root] = tree[pre];
        tree[root].max = max(tree[root].max, tag);
        if (ql <= l && r <= qr) {
            tree[root].tag = max(tree[root].tag, tag);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(newNd(ls(root)), ls(pre), l, mid, ql, qr, tag);
        if (qr > mid) modify(newNd(rs(root)), rs(pre), mid + 1, r, ql, qr, tag);
    }

    int query(int root, int l, int r, int ql, int qr) {
        int res = tree[root].tag;
        if (ql <= l && r <= qr) return max(res, tree[root].max);
        int mid = (l + r) >> 1;
        if (ql <= mid) res = max(res, query(ls(root), l, mid, ql, qr));
        if (qr > mid) res = max(res, query(rs(root), mid + 1, r, ql, qr));
        return res;
    }

    void clear() {
        for (int i = 0; i <= n; i++) g[i].clear(), g2[i].clear();
        for (int i = 0; i <= tot; i++)
            tree[i].lson = tree[i].rson = tree[i].max = 0, tree[i].tag = -1;
        tot = tim = 0, ans = 1;
        for (int i = 0; i <= n; i++) root[i] = 0, dp[i] = 0;
    }

    void dfs2(int cur, int f) {
        L[cur] = ++tim, sz[cur] = 1;
        for (auto& to : g2[cur]) {
            if (to == f) continue;
            dfs2(to, cur);
            sz[cur] += sz[to];
        }
    }

    void init() { build(newNd(root[0]), 1, n); }

    void dfs1(int cur, int f) {
        depth[cur] = depth[f] + 1;
        int mx = query(root[f], 1, n, L[cur], L[cur] + sz[cur] - 1);
        dp[cur] = min(dp[f] + 1, depth[cur] - mx); // 答案至多是 ans[fa] + 1 因为当前只对 cur 进行判断
        modify(newNd(root[cur]), root[f], 1, n, L[cur], L[cur] + sz[cur] - 1, depth[cur]);
        for (auto& to : g[cur]) {
            if (to == f) continue;
            dfs1(to, cur);
        }
    }
}

int main() {
    boost;
    cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            g[u].push_back(v), g[v].push_back(u);
        }
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            g2[u].push_back(v), g2[v].push_back(u);
        }
        Solution::dfs2(1, 0);
        Solution::init();
        Solution::dfs1(1, 0);
        for (int i = 1; i <= n; i++) Solution::ans = max(Solution::ans, Solution::dp[i]);
        cout << Solution::ans << "\n";
        Solution::clear();
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
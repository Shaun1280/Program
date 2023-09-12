#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF383C
using namespace std;
using LL = long long;
//奇数层+，偶数层-
template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

int n, m;
array<int, MAXN> a, sz, in, depth, from;
vector<int> g[MAXN];

template <int MAXN>
struct BIT {
    using LL = long long
    struct Bit {
        int lowbit(int x) { return x & (-x); }

        void build(int x = 2, int sub = 1) {
            while (x <= n) {
                for (int i = x; i <= n; i += x)
                    c[i] += c[i - sub];  //加上儿i - sub子的c
                x <<= 1, sub <<= 1;      // 2 ^ n
            }
        }

        void add(int x, LL val) {
            while (x <= n) c[x] += val, x += lowbit(x);
        }

        LL query(int x, LL res = 0) {
            while (x) res += c[x], x -= lowbit(x);
            return res;
        }
        array<LL, MAXN> c;
    } bit[3];

    inline void add(int l, int r, LL val) {
        bit[1].add(l, val), bit[1].add(r + 1, -val);
        bit[2].add(l, val * l), bit[2].add(r + 1, -val * (r + 1));
    }

    inline LL query(int l, int r, LL res = 0) {
        res = bit[0].query(r) + bit[1].query(r) * (r + 1) - bit[2].query(r);
        res -=
            bit[0].query(l - 1) + bit[1].query(l - 1) * l - bit[2].query(l - 1);
        return res;
    }
};
BIT<MAXN> bit;

void dfs(int cur, int f) {
    static int tot;
    sz[cur] = 1, in[cur] = ++tot;
    from[tot] = cur, depth[cur] = depth[f] + 1;
    for (auto& to : g[cur]) {
        if (to == f) continue;
        dfs(to, cur);
        sz[cur] += sz[to];
    }
}

int main() {
    read(n, m);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1, u, v; i < n; i++) {
        read(u, v);
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs(1, 0);
    while (m--) {
        int opt, x, val;
        read(opt, x);
        if (opt == 1) {
            read(val);
            if (depth[x] & 1) bit.add(in[x], in[x] + sz[x] - 1, val);
            else bit.add(in[x], in[x] + sz[x] - 1, -val);
        } else {
            LL tmp = bit.query(in[x], in[x]);
            if (depth[x] & 1) printf("%lld\n", a[x] + tmp);
            else printf("%lld\n", a[x] - tmp);
        }
    }
    return 0;
}
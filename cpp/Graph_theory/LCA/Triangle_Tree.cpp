#include <bits/stdc++.h>

// https://codeforces.com/contest/2063/problem/E
// lca dist triangle property

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

#define error(args...)                                                         \
    {                                                                          \
        string _s = #args;                                                     \
        replace(_s.begin(), _s.end(), ',', ' ');                               \
        stringstream _ss(_s);                                                  \
        istream_iterator<string> _it(_ss);                                     \
        err(_it, args);                                                        \
    }

void err(istream_iterator<string> it) { cout << endl; }

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << " ";
    err(++it, args...);
}

template <typename T> inline void read(T& x) {
    x = 0;
    T f = 1;
    char ch = getchar();
    while (!isdigit(ch))
        f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch))
        x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template <typename T, typename... Args> inline void read(T& x, Args&... args) {
    read(x), read(args...);
}

template <typename T> inline void write(T x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}

template <typename T, typename... Args> inline void write(T& x, Args&... args) {
    write(x), putchar('\n'), write(args...);
}

constexpr int MAXN = 3e5 + 5, MOD = 1e9 + 7;

vector<int> g[MAXN];
array<int, MAXN> d, cntd, sufd, sz;

void solveOne(int ncase) {
    int n;
    cin >> n;

    for (int i = 0; i <= n + 1; ++i) {
        g[i].clear();
        d[i] = sz[i] = sufd[i] = cntd[i] = 0;
    }

    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto dfs1 = [&](auto dfs1, int cur, int fa = -1) -> void {
        ++cntd[d[cur]], sz[cur] = 1;
        for (const auto& to : g[cur]) {
            if (to == fa)
                continue;
            d[to] = d[cur] + 1;
            dfs1(dfs1, to, cur);
            sz[cur] += sz[to];
        }
    };

    dfs1(dfs1, 1);

    for (int i = n; i >= 0; --i) {
        sufd[i] = sufd[i + 1] + cntd[i];
    }

    long long ans{0};
    for (int i = 1; i <= n; ++i) {
        ans += 2LL * d[i] * (sufd[d[i] + 1] + cntd[d[i]] - sz[i]);
        --cntd[d[i]];
    }

    auto dfs2 = [&](auto dfs2, int cur, int fa = -1) -> void {
        long long sum{0};
        for (const auto& to : g[cur]) {
            if (to == fa)
                continue;
            sum += sz[to];
            dfs2(dfs2, to, cur);
        }

        long long tmp{0};
        for (const auto& to : g[cur]) {
            if (to == fa)
                continue;
            tmp += 1LL * sz[to] * (sum - sz[to]);
        }

        ans -= tmp / 2 * (2 * d[cur] + 1);
    };

    dfs2(dfs2, 1);

    cout << ans << "\n";
}

int main() {
    boost;
    int testcase = 1;
    cin >> testcase;
    for (int i = 1; i <= testcase; i++)
        solveOne(i);
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
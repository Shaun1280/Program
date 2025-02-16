#include <bits/stdc++.h>

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

template <typename T> inline void read(T &x) {
    x = 0;
    T f = 1;
    char ch = getchar();
    while (!isdigit(ch))
        f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch))
        x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template <typename T, typename... Args> inline void read(T &x, Args &...args) {
    read(x), read(args...);
}

template <typename T> inline void write(T x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}

template <typename T, typename... Args> inline void write(T &x, Args &...args) {
    write(x), putchar('\n'), write(args...);
}

constexpr int MAXN = 2e5 + 5, MOD = 998244353;

array<int, MAXN> a;

void solveOne(int ncase) {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    vector<int> dp(n + 1, INT_MAX), ans(k + 1);
    vector<vector<pair<int, int>>> rGroups(n + 1);

    for (int i = 1; i <= k; ++i) {
        int r, x;
        cin >> r >> x;
        rGroups[r].emplace_back(x, i);
    }

    // LIS
    dp[0] = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        auto idx = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        // error(idx);
        dp[idx] = a[i];
        for (const auto &[x, idx] : rGroups[i]) {
            ans[idx] = upper_bound(dp.begin(), dp.end(), x) - dp.begin();
        }
    }

    for (int i = 1; i <= k; ++i) {
        cout << ans[i] - 1 << "\n";
    }
}

int main() {
    boost;
    int testcase = 1;
    // cin >> testcase;
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
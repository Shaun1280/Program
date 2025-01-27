#include <bits/stdc++.h>

// Codeforces Round 1000 (Div. 2) D
// https://codeforces.com/contest/2063/problem/D

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

constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;

void solveOne(int ncase) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    vector<long long> f(n), g(m);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a.begin(), a.end());

    for (int i = 1; i * 2 <= n; ++i) {
        f[i] = f[i - 1] + a[n - i] - a[i - 1];
    }

    for (int i = 0; i < m; i++)
        cin >> b[i];

    sort(b.begin(), b.end());

    for (int i = 1; i * 2 <= m; ++i) {
        g[i] = g[i - 1] + b[m - i] - b[i - 1];
    }

    int k_max = min((n + m) / 3, min(n, m));

    cout << k_max << "\n";

    auto calc = [&](int k, int x) -> long long {
        int y{k - x};
        return f[x] + g[y];
    };

    for (int k = 1; k <= k_max; ++k) {
        // x + y = k
        int l{max(0, 2 * k - m)}, r(min({n / 2, n - k, k}));
        long long res{0};
        while (r - l >= 3) {
            int lmid = (l + l + r) / 3, rmid = (l + r + r) / 3;
            long long lval = calc(k, lmid), rval = calc(k, rmid);
            if (lval > rval)
                r = rmid;
            else
                l = lmid;
        }
        for (int i = l; i <= r; ++i) {
            res = max(res, calc(k, i));
        }
        cout << res << " ";
    }
    cout << "\n";
}

int main() {
    boost;
    int testcase = 1;
    cin >> testcase;
    for (int i = 1; i <= testcase; i++)
        solveOne(i);
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define PI acos(-1)
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

constexpr int MAXN = 1e6 + 6;

namespace NTT {
    constexpr int NR = 1 << 22, g = 3, gi = 332748118, mod = 998244353;

    long long qpow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    int R[4000001];
    void init(int& sz) {
        if (__builtin_popcount(sz) != 1) sz = 1 << (1 + (int)log2(sz));
        for (int i = 0; i < sz; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (sz >> 1) : 0);
    }

    void dft(long long a[], int sz, int type) {
        for (int i = 0; i < sz; i++)
            if (i < R[i]) swap(a[i], a[R[i]]);
        for (int m = 2; m <= sz; m <<= 1) {
            long long gn = qpow(type == 1 ? g : gi, (mod - 1) / m); // 单位原根 g_n
            for (int k = 0; k < sz; k += m) {
                long long g0(1);
                for (int j = 0; j < m / 2; j++) {
                    long long t = g0 * a[k + j + m / 2] % mod;
                    long long u = a[k + j];
                    a[k + j] = (u + t) % mod;
                    a[k + j + m / 2] = (u - t + mod) % mod;
                    g0 = g0 * gn % mod;
                }
            }
        }
        if (type == -1) {
            long long inv = qpow(sz, mod - 2);
            for (int i = 0; i < sz; i++) a[i] = a[i] * inv % mod;
        }
    }
}

namespace Polynomial {
    using namespace NTT;

    void Convolution(int n, int m, int a[], int b[], int c[]) { // a[0, n] b[0, m]
        int N = n + m + 1;
        init(N);
        long long f[N], g[N];
        for (int i = 0; i < N; i++) f[i] = g[i] = 0;
        for (int i = 0; i <= n; i++) f[i] = a[i];
        for (int i = 0; i <= m; i++) g[i] = b[i];
        dft(f, N, 1), dft(g, N, 1);
        long long res[N];
        for (int i = 0; i < N; i++) res[i] = 0;
        for (int i = 0; i < N; i++) res[i] = f[i] * g[i] % mod;
        dft(res, N, -1);
        for (int i = 0; i <= n + m; i++) c[i] = res[i];
    }
};

int a[MAXN], b[MAXN], c[MAXN * 2];

int main() {
    int n, m, N;
    read(n, m);
    for (int i = 0; i <= n; i++) read(a[i]);
    for (int i = 0; i <= m; i++) read(b[i]);
    Polynomial::Convolution(n, m, a, b, c);
    for (int i = 0; i <= n + m; i++) printf("%d ", c[i]);
    return 0;
}
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
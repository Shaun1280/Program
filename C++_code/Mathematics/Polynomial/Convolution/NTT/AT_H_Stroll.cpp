#include <bits/stdc++.h>

using namespace std;

#define debug(x) cerr << #x << " = " << x << endl
#define PI acos(-1)
#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e5 + 5;

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

    void DivideAndConquerNTT(int a[], int b[], int l, int r) { // f[i] = \sum f[i-j]*g[j]
        if (l == r) {
            if (!l) a[l] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        DivideAndConquerNTT(a, b, l, mid); // 求出左半部分 f
        int f[mid - l + 1], g[r - l + 1], c[r - l + 1 + mid - l + 1];
        for (int i = 0; i < mid - l + 1; i++) f[i] = a[i + l];
        for (int i = 0; i < r - l + 1; i++) g[i] = b[i];
        Convolution(mid - l, r - l, f, g, c);
        for (int i = mid + 1; i <= r; i++) a[i] = (a[i] + c[i - l]) % mod;
        // 对右半部分贡献为 w_x = \sum_i={l, mid} f[i]*g[x-i] 通过卷积实现
        DivideAndConquerNTT(a, b, mid + 1, r);
    }
};

int n;
int f[MAXN], g[MAXN];

int main() {
    boost;
    cin >> n;
    for (int i = 1; i < n; i++) cin >> g[i];
    Polynomial::DivideAndConquerNTT(f, g, 0, n - 1);
    for (int i = 0; i < n; i++) cout << f[i] << " ";
    return 0;
}
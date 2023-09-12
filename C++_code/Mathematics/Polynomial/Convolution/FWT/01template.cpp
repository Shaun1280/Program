#include <bits/stdc++.h>
// https://www.luogu.com.cn/problem/P4717
// P4717 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)
using namespace std;

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args&... args) { read(x), read(args...); }

template<typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}

template<typename T, typename ...Args>
inline void write(T& x , Args&... args) { write(x), putchar('\n'), write(args...); }

constexpr int MAXN = 1 << 17, MOD = 998244353;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

namespace FWT {
    void init(int& sz) {
        if (__builtin_popcount(sz) != 1) sz = 1 << (1 + (int)log2(sz));
    }

    void _or(int a[], int sz, int type) {
        for (int i = 1; i < sz; i <<= 1)
            for (int j = 0; j < sz; j += (i << 1))
                for (int k = 0; k < i; k++)
                    a[j + k + i] = ((a[j + k + i] + a[j + k] * type) % MOD + MOD) % MOD;
    }

    void _and(int a[], int sz, int type) {
        for (int i = 1; i < sz; i <<= 1)
            for (int j = 0; j < sz; j += (i << 1))
                for (int k = 0; k < i; k++)
                    a[j + k] = ((a[j + k] + a[j + k + i] * type) % MOD + MOD) % MOD;
    }
    
    void _xor(int a[], int sz, int type) {
        for (int i = 1; i < sz; i <<= 1)
            for (int j = 0; j < sz; j += (i << 1))
                for (int k = 0; k < i; k++) {
                    int x = a[j + k], y = a[j + k + i];
                    a[j + k] = (x + y) % MOD, a[j + k + i] = ((x - y) % MOD + MOD) % MOD;
                }
        if (type == -1) {
            int tmp = qpow(sz, MOD - 2);
            for (int i = 0; i < sz; i++) a[i] = 1LL * a[i] * tmp % MOD;
        }
    }
}

int a[MAXN], b[MAXN];

int main() {
    int n;
    read(n);
    int f[1 << n], g[1 << n];
    for (int i = 0; i < (1 << n); i++) cin >> a[i];
    for (int i = 0; i < (1 << n); i++) cin >> b[i];

    for (int i = 0; i < (1 << n); i++) f[i] = a[i], g[i] = b[i];
    FWT::_or(f, 1 << n, 1), FWT::_or(g, 1 << n, 1);
    for (int i = 0; i < (1 << n); i++) f[i] = 1LL * f[i] * g[i] % MOD;
    FWT::_or(f, 1 << n, -1);
    for (int i = 0; i < (1 << n); i++) write(f[i]), putchar(' ');
    putchar('\n');

    for (int i = 0; i < (1 << n); i++) f[i] = a[i], g[i] = b[i];
    FWT::_and(f, 1 << n, 1), FWT::_and(g, 1 << n, 1);
    for (int i = 0; i < (1 << n); i++) f[i] = 1LL * f[i] * g[i] % MOD;
    FWT::_and(f, 1 << n, -1);
    for (int i = 0; i < (1 << n); i++) write(f[i]), putchar(' ');
    putchar('\n');

    for (int i = 0; i < (1 << n); i++) f[i] = a[i], g[i] = b[i];
    FWT::_xor(f, 1 << n, 1), FWT::_xor(g, 1 << n, 1);
    for (int i = 0; i < (1 << n); i++) f[i] = 1LL * f[i] * g[i] % MOD;
    FWT::_xor(f, 1 << n, -1);
    for (int i = 0; i < (1 << n); i++) write(f[i]), putchar(' ');
    putchar('\n');
    return 0;
}
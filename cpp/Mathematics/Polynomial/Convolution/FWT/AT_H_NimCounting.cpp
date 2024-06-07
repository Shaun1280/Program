#include <bits/stdc++.h>
// https://atcoder.jp/contests/abc212/tasks/abc212_h Nim counting
// 可以选 1 <= M <= N 堆石子，每堆石子个数从 (A1, A2, ... Ak) 中选择
// 问最后 Nim 游戏胜利的石子选择方案数
// 问题等于 N 次卷积，每次卷积后下标大于 0 的位置的和
// 通过 fwt 转为点值表示，每一下标的贡献可以通过等比数列求和得到 0
// 注意下标 0 也要带入卷积，但最后不计入答案
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

int n, ans, mx, k;
int c[MAXN];

int main() {
    read(n, k);
    for (int i = 1, x; i <= k; i++) cin >> x, c[x] = 1, mx = max(mx, x);
    int sz = mx + 1;
    FWT::init(sz);
    FWT::_xor(c, sz, 1);
    // ans = sum of [1, ... len - 1] of C, C^2, C^3, ..., C^n
    // after fwt ans = sum of [1, ... len - 1] (ci + ci^2+....+ci^n)
    // geometric sequence
    for (int i = 0; i < sz; i++) {
        if (c[i] == 0) continue;
        else if (c[i] == 1) c[i] = n;
        else {
            c[i] = 1LL * c[i] * (qpow(c[i], n) - 1) % MOD * qpow(c[i] - 1, MOD - 2) % MOD;
            if (c[i] < 0) c[i] += MOD;
        }
    }
    FWT::_xor(c, sz, -1);
    for (int i = 1; i < sz; i++) ans = (ans + c[i]) % MOD;
    write(ans);
    return 0;
}
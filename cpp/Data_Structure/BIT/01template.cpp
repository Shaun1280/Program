#include <bits/stdc++.h>

using namespace std;
using LL = long long;

constexpr int MAXN = 1e5 + 5;

int n;

struct BIT { //Binary Index Trees, 1based
    int lowbit(int x) { return x & (~x + 1); }
    /* O(n) 建树*/
    void build(int x = 2, int sub = 1) {
        while (x <= n) {
            for (int i = x; i <= n; i += x)
                c[i] += c[i - sub];  //加上儿i - sub子的c
            x <<= 1, sub <<= 1;      // 2 ^ n
        }
    }
    /*@param x the position to add val*/
    void add(int x, LL val) {
        while (x <= n) c[x] += val, x += lowbit(x);
    }
    /*查询 [1, x] 的前缀和*/
    LL query(int x, LL res = 0) {
        while (x) res += c[x], x -= lowbit(x);
        return res;
    }
    array<LL, MAXN> c;
} bit[3];
/*range [l, r] add val*/
inline void add(int l, int r, LL val) {
    bit[1].add(l, val), bit[1].add(r + 1, -val);
    bit[2].add(l, val * l), bit[2].add(r + 1, -val * (r + 1));
}
/*range [l, r] sum query*/
inline LL query(int l, int r, LL res = 0) {
    res = bit[0].query(r) + bit[1].query(r) * (r + 1) - bit[2].query(r);
    res -= bit[0].query(l - 1) + bit[1].query(l - 1) * l - bit[2].query(l - 1);
    return res;
}
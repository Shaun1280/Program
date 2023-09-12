#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/T123572
constexpr int MAXN = 3e5 + 5;
constexpr long long M = 998244353;

using namespace std;

template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct segTree {
    segTree *lson, *rson;
    int l, r;
    long long mul;
}Tree[MAXN << 1];
int tot, n, q, x;
long long arr[MAXN];
using Node = segTree *;
#define Lson root->lson
#define Rson root->rson

inline void build (int L, int R, Node root) {
    root->l = L, root->r = R;
    if (L == R) {
        root->mul = (arr[L]) % M;
        return;
    }
    int mid = (L + R) >> 1;
    Lson = &Tree[++tot], Rson = &Tree[++tot];
    build (L, mid, Lson), build(mid + 1, R, Rson);
    root->mul = Lson->mul * Rson->mul % M;
}

inline long long query (int L, int R, Node root) {
    if (L <= root->l && root->r <= R) {
        return root->mul;
    }
    int mid = (root->l + root->r) >> 1;
    long long res = 1;
    if (L <= mid) res = res * query(L, R, Lson) % M;
    if (R > mid) res = res * query(L, R, Rson) % M;
    return res;
}

inline int getMiu(long long val) {
    if (val == 1) return 1;
    int miu = 1;
    long long cpy = val, cnt = 0;
    for (int i = 2; i <= sqrt(cpy); i++) {
        if (val % i == 0) {
            miu = -miu, val /= i;
            if (val % i == 0) return 0;
        }
    }
    if (val != 1) miu = -miu;
    return miu;
}

int main() {
    read(n), read(q), read(x);
    for (long long i = 1, tmp; i <= n; i++) 
        read(tmp), arr[i] = tmp + getMiu(tmp) + x;
    build(1, n, Tree);
    while (q--) {
        int l, r;
        read(l), read(r);
        printf("%lld\n", query(l, r, Tree));
    }
    return 0;
}
#include <bits/stdc++.h>
// cat tree linear base merge
// Time & space (nlogn2)
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = (1 << 17) + 2, LOG = 17, MOD = 1e9 + 7;

template<typename T, const int LIM>
struct LinearCombination {
    void init() { fill(p, p + LIM + 1, 0); }

    void insert(const LinearCombination<T, LIM>& pre, T x) {
        *this = pre;
        for (int i = LIM; ~i; i--) {
            if (x >> i) { // x 第 i 位为 1
                if (!p[i]) {
                    p[i] = x;
                    break;
                }
                x ^= p[i];
            }
        }
    }

    // 集合内任意几个元素 xor 的最大值
    T qmax(T x = 0) {
        T res(x);
        for (int i = LIM; ~i; i--) res = max(res, res ^ p[i]);
        return res;
    }

    void merge(const LinearCombination<T, LIM>& other) {
        for (int i = 0; i <= LIM; i++) {
            int x = other.p[i];
            for (int j = LIM; j >= 0; j--) {
                if (x >> j) {
                    if (!this->p[j]) {
                        this->p[j] = x;
                        break;
                    }
                    x ^= this->p[j];
                }
            }
        }
    }

    T p[LIM + 1];
};

template<typename T, const int MAXN, const int LIM>
struct Cat_t {
    #define ls(x) (x << 1)
    #define rs(x) (x << 1 | 1)
    LinearCombination<T, LIM> f[LOG + 1][MAXN], empty;
    int depth[MAXN << 2], log[MAXN << 2], id[MAXN];

    void init() {
        log[0] = 0;
        for (int i = 1; i < MAXN * 4; i++) log[i] = log[i >> 1] + 1;
    }

    void build(int x, int l, int r, int d, T* a) {
        depth[x] = d;
        if (l == r) { f[d][l].insert(empty, a[l]); id[l] = x; return; }
        int mid = (l + r) >> 1;
        f[d][mid].insert(empty, a[mid]);
        for (int i = mid - 1; i >= l; i--)
            f[d][i].insert(f[d][i + 1], a[i]); // prefix
        f[d][mid + 1].insert(empty, a[mid + 1]);
        for (int i = mid + 2; i <= r; i++)
            f[d][i].insert(f[d][i - 1], a[i]); // suffix
        build(ls(x), l, mid, d + 1, a);
        build(rs(x), mid + 1, r, d + 1, a);
    }

    LinearCombination<T, LIM> query(int l, int r) {
        int x = id[l], y = id[r];
        int lca = (x >> log[x ^ y]), d = depth[lca];
        LinearCombination<T, LIM> ret = f[d][l];
        ret.merge(f[d][r]);
        return ret;
    }
};
Cat_t<int, MAXN, 20> ct;

int n, q;
int a[MAXN];

int main() {
    boost;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int D = 1;
    while (D < n) D <<= 1;
    ct.init();
    ct.build(1, 1, D, 0, a);
    cin >> q;
    for (int i = 1, l, r; i <= q; i++) {
        cin >> l >> r;
        cout << ct.query(l, r).qmax() << "\n";
    }
    return 0;
}
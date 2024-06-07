#include <bits/stdc++.h>

using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 4e5 + 6, MOD = 1e9 + 7;

template<typename T, const int LIM>
struct PrefixLinearCombination {
    void init() { fill(p, p + LIM + 1, 0); fill(pos, pos + LIM + 1, 0); }

    void insert(const PrefixLinearCombination<T, LIM>& pre, T x, int pos) {
        *this = pre;
        for (int i = LIM; ~i; i--) {
            if (x >> i) { // x 第 i 位为 1
                if (!p[i]) {
                    p[i] = x;
                    this->pos[i] = pos;
                    break;
                } else if (this->pos[i] < pos) swap(p[i], x), swap(this->pos[i], pos);
                x ^= p[i];
            }
        }
    }

    bool query(T x, int l) { // range query whether x can be obtained
        T res(x);
        for (int i = LIM; ~i; i--) {
            if (((res >> i) & 1) && pos[i] >= l) res ^= p[i];
        }
        return res == 0;
    }
    T p[LIM + 1];
    int pos[LIM + 1];
};
PrefixLinearCombination<long long, 63> lc[MAXN];

int main() {
    boost;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        lc[i].insert(lc[i - 1], x, i);
    }
    for (int i = 1; i <= q; i++) {
        int l, r; long long x;
        cin >> l >> r >> x;
        if (lc[r].query(x, l)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
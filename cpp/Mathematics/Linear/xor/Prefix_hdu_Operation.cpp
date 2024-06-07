#include <bits/stdc++.h>
// There is an integer sequence a of length n and there are two kinds of operations:
// 0 l r: select some numbers from al...ar so that their xor sum is maximum, and print the maximum value.
// 1 x: append x to the end of the sequence and let n=n+1.

using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

constexpr int MAXN = 1e6 + 6, MOD = 1e9 + 7;

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

    // 集合内任意几个元素 xor 的最大值
    T qmax(int l) { // 将线性基从高位向低位扫，若 xor 上当前扫到的 pi 答案变大，就把答案异或上 pi。
        T res(0);
        for (int i = LIM; ~i; i--) {
            if (pos[i] >= l) res = max(res, res ^ p[i]);
        }
        return res;
    }
    T p[LIM + 1];
    int pos[LIM + 1];
};
PrefixLinearCombination<int, 30> lc[MAXN];

int main() {
    boost;
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m, lastans(0);
        cin >> n >> m;
        for (int i = 1; i <= n + m; i++) lc[i].init();
        for (int i = 1, x; i <= n; i++) {
            cin >> x;
            lc[i].insert(lc[i - 1], x, i);
        }
        for (int i = 1, opt, l, r; i <= m; i++) {
            cin >> opt;
            if (opt == 0) {
                cin >> l >> r;
                l = (l ^ lastans) % n + 1, r = (r ^ lastans) % n + 1;
                if (l > r) swap(l, r);
                cout << (lastans = lc[r].qmax(l)) << "\n";
            } else {
                cin >> l;
                l ^= lastans, n++;
                lc[n].insert(lc[n - 1], l, n);
            }
        }
    }
    return 0;
}
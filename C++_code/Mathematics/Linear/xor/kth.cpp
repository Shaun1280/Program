#include <bits/stdc++.h>
// 查询给出的数能异或出的第 k 小的数（包括 0)
using namespace std;

#define boost ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

template<typename T, const int LIM>
struct LinearCombination {
    void init() { fill(p, p + LIM + 1, 0); zero = false; }

    void insert(T x) {
        for (int i = LIM; ~i; i--) {
            if (x >> i) { // x 第 i 位为 1
                if (!p[i]) {
                    p[i] = x;
                    break;
                }
                x ^= p[i];
            }
        }
        if (!x) zero = true;
    }

    // 集合内任意几个元素 xor 的最大值
    T qmax() { // 将线性基从高位向低位扫，若 xor 上当前扫到的 pi 答案变大，就把答案异或上 pi。
        T res(0);
        for (int i = LIM; ~i; i--) {
            res = max(res, res ^ p[i]);
        }
        return res;
    }

    bool query(T x = 0) { // 类似于插入，如果最后插入的数 x 被异或成了 0，则能被异或出来
        T res(x);
        for (int i = LIM; ~i; i--) {
            if (x >> i) {
                if (!p[i]) break;
                x ^= p[i];
            }
        }
        return x == 0;
    }

    T kth(T k) { // 返回异或出的第 k 大数 xor bi * ki
        if (zero) k--;
        T tmp[LIM + 1], res(0), cnt(0);
        copy(p, p + LIM + 1, tmp);

        for (int i = LIM; ~i; i--) {
            for (int j = i - 1; ~j; j--)
                if ((tmp[i] >> j) & 1) tmp[i] ^= tmp[j];
        }
        for (int i = 0; i <= LIM; i++) if (tmp[i]) tmp[cnt++] = tmp[i];

        if (k >> cnt) return -1;
        for (int i = 0; i < cnt; i++)
            if ((k >> i) & 1) res ^= tmp[i];
        return res;
    }

    T p[LIM + 1];
    bool zero;
};
LinearCombination<long long, 63> lc; // 0-63 共 64位


void solveOne(int ncase) {
    cout << "Case #" << ncase << ":\n";
    lc.init();
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        long long tmp;
        cin >> tmp;
        lc.insert(tmp);
    }

    cin >> q;
    while (q--) {
        long long k;
        cin >> k;
        cout << lc.kth(k) << "\n";
    }
}

int main() {
    boost;
    int testcase = 1;
    cin >> testcase;
    for (int i = 1; i <= testcase; i++) solveOne(i);
    return 0;
}
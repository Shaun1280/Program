#include <bits/stdc++.h>

using namespace std;

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
    T qmax(T x = 0) { // 将线性基从高位向低位扫，若 xor 上当前扫到的 pi 答案变大，就把答案异或上 pi。
        T res(x);
        for (int i = LIM; ~i; i--) {
            res = max(res, res ^ p[i]);
        }
        return res;
    }

    bool query(T x) { // 类似于插入，如果最后插入的数 x 被异或成了 0，则能被异或出来
        T res(0);
        for (int i = LIM; ~i; i--) {
            if (x >> i) {
                if (!p[i]) break;
                x ^= p[i];
            }
        }
        return x == 0;
    }

    T kth(T k) { // 返回异或出的第 k 大数 xor bi * ki
        if (zero) k--; // 线性基没有异或为 0 的子集，如果插入时结果为 0，说明能够异或出 0
        T tmp[LIM + 1], res(0), cnt(0);
        copy(p, p + LIM + 1, tmp);

        for (int i = LIM; ~i; i--) { // 将每一位独立，只有 p[i] 的第 i 位为 1
            for (int j = i - 1; ~j; j--)
                if ((tmp[i] >> j) & 1) tmp[i] ^= tmp[j];
        }
        for (int i = 0; i <= LIM; i++) if (tmp[i]) tmp[cnt++] = tmp[i]; // 提取出 2^i

        if (k >> cnt) return -1;
        for (int i = 0; i < cnt; i++)
            if ((k >> i) & 1) res ^= tmp[i];
        return res;
    }

    T p[LIM + 1];
    bool zero;
};
LinearCombination<long long, 63> lc; // 0-63 共 64位

#include <bits/stdc++.h>

using namespace std;

template<typename T>
inline void read(T& x) {
    x = 0; T f = 1; char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

template<typename T, typename ...Args>
inline void read(T& x, Args& ...args) { read(x), read(args...); }

namespace GenHelper {
unsigned z1, z2, z3, z4, b;
unsigned rand_() {
    b = ((z1 << 6) ^ z1) >> 13;
    z1 = ((z1 & 4294967294U) << 18) ^ b;
    b = ((z2 << 2) ^ z2) >> 27;
    z2 = ((z2 & 4294967288U) << 2) ^ b;
    b = ((z3 << 13) ^ z3) >> 21;
    z3 = ((z3 & 4294967280U) << 7) ^ b;
    b = ((z4 << 3) ^ z4) >> 12;
    z4 = ((z4 & 4294967168U) << 13) ^ b;
    return (z1 ^ z2 ^ z3 ^ z4);
}
}  // namespace GenHelper
void srand(unsigned x) {
    using namespace GenHelper;
    z1 = x;
    z2 = (~x) ^ 0x233333333U;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
}
int read() {
    using namespace GenHelper;
    int a = rand_() & 32767;
    int b = rand_() & 32767;
    return a * 32768 + b;
}

struct Cartesian {
    void build(vector<int>& a) {
        stk.resize(a.size()), lson.resize(a.size()), rson.resize(a.size());
        for (int i = 0; i < a.size(); i++) { // <= 大根堆 
            while (top && a[stk[top]] <= a[i]) lson[i] = stk[top--];
            rson[stk[top]] = i;
            stk[++top] = i;
        }
        root = stk[1];
    }

    int query(int l, int r) { //返回最大/最小值下标
        int root = this->root;
        while (root < l || root > r)
            root = (root < l ? rson[root] : lson[root]);
        return root;
    }

    int root = 0, top = 0;
    vector<int> stk, lson, rson;
} T;

int n, m, s;
unsigned long long sum;
vector<int> a;

int main() {
    read(n, m, s), srand(s), a.resize(n);
    for (auto& i : a) i = read();
    T.build(a);
    for (int i = 0, l, r; i < m; i++) {
        l = read() % n, r = read() % n;
        if (l > r) swap(l, r);
        sum += a[T.query(l, r)];
    }
    printf("%llu\n", sum);
    return 0;
}
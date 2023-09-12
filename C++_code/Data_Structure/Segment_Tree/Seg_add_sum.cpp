#include <bits/stdc++.h>
const int maxn = 1e6 + 6;
typedef long long LL;
#define L(x) (x << 1)      // x*2
#define R(x) (x << 1 | 1)  // x*2+1
using namespace std;
LL num[maxn];
inline LL read() {
    LL x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') f = (ch == '-') ? -1 : 1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
class Seg_tree {
   private:
    struct S {
        LL l, r;
        LL sum, add;
    } Tree[maxn << 2];

   public:
    inline void update(LL node)  // push up
    {
        Tree[node].sum = Tree[L(node)].sum + Tree[R(node)].sum;
        return;
    }
    inline void build(LL left, LL right, LL node) {
        Tree[node].l = left, Tree[node].r = right;
        Tree[node].add = 0;  //!!
        if (left == right) {
            Tree[node].sum = num[left];
            return;
        }
        LL mid = (Tree[node].l + Tree[node].r) >> 1;
        build(left, mid, L(node));
        build(mid + 1, right, R(node));
        update(node);  //!!
        return;
    }
    inline void Push_tag(LL node) {
        if (!Tree[node].add) return;
        LL l = Tree[node].l, r = Tree[node].r;
        LL mid = (l + r) >> 1;
        Tree[L(node)].add += Tree[node].add;
        Tree[R(node)].add += Tree[node].add;
        Tree[L(node)].sum += Tree[node].add * (mid - l + 1);
        Tree[R(node)].sum += Tree[node].add * (r - mid);  // r-(mid+1)-1
        Tree[node].add = 0;
        return;
    }
    inline void Seg_change(LL left, LL right, LL node, LL val) {
        if (left == Tree[node].l && right == Tree[node].r) {
            Tree[node].sum += val * (right - left + 1);
            Tree[node].add = val;
            return;
        }
        Push_tag(node);
        LL mid = (Tree[node].l + Tree[node].r) >> 1;
        if (right <= mid)
            Seg_change(left, right, L(node), val);
        else if (left > mid)
            Seg_change(left, right, R(node), val);
        else
            Seg_change(left, mid, L(node), val),
                Seg_change(mid + 1, right, R(node), val);
        update(node);  //!!
        return;
    }
    inline LL ask_sum(LL left, LL right, LL node) {
        if (Tree[node].l >= left && Tree[node].r <= right)
            return Tree[node].sum;
        Push_tag(node);
        LL mid = (Tree[node].l + Tree[node].r) >> 1;
        if (right <= mid)
            return ask_sum(left, right, L(node));
        else if (left > mid)
            return ask_sum(left, right, R(node));
        else
            return ask_sum(left, mid, L(node)) +
                   ask_sum(mid + 1, right, R(node));
    }
    inline LL ask_sum2(LL left, LL right, LL node) {
        if (left <= Tree[node].l && Tree[node].r <= r) return Tree[node].sum;
        Push_tag(node);
        LL res = 0;
        LL mid = (Tree[node].l + Tree[node].r) >> 1;
        if (left <= mid) res += ask_sum2(left, right, L(node));
        if (r > mid) res += ask_sum2(left, right, R(node));
        return res;
    }
} T;
LL n, m, opt, l, r, val;
int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; i++) num[i] = read();
    T.build(1, n, 1);
    while (m--) {
        opt = read();
        switch (opt) {
            case 1:
                l = read(), r = read(), val = read(),
                T.Seg_change(l, r, 1, val);
                break;
            case 2:
                l = read(), r = read(), printf("%lld\n", T.ask_sum(l, r, 1));
                break;
        }
    }
    return 0;
}

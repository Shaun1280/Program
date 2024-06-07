#include <bits/stdc++.h>
// persistent segment tree range update
// SP11470 TTM - To the moon
constexpr int MAXN = 5e5 + 5;
constexpr int LOG = 20;
typedef long long LL;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
struct Node {
    Node *lson, *rson;
    LL sum, add;
} Tree[MAXN * LOG], *rt[MAXN];
#define Lson root->lson
#define Rson root->rson
int tot, n, m, arr[MAXN], T;
inline Node *newNode(Node *&root) { return root = &Tree[++tot]; }
inline void build(int L, int R, Node *root) {
    if (L == R) {
        root->sum = arr[L];
        return;
    }
    int mid = (L + R) >> 1;
    build(L, mid, newNode(Lson)), build(mid + 1, R, newNode(Rson));
    root->sum = Lson->sum + Rson->sum;
}
inline void modify(Node *pre, Node *root, int L, int R, int qL, int qR, int d) {
    *root = *pre;              //拷贝
    if (qL <= L && R <= qR) {  //区间被包含 加上永久标记
        root->add += d;
        return;
    }
    int mid = (L + R) >> 1;
    if (qL <= mid) modify(pre->lson, newNode(Lson), L, mid, qL, qR, d);
    if (qR > mid) modify(pre->rson, newNode(Rson), mid + 1, R, qL, qR, d);
    root->sum = Lson->sum + Rson->sum + (mid - L + 1) * Lson->add +
                (R - mid) * Rson->add;  // update
}
inline LL query(Node *root, int L, int R, int qL, int qR, LL add) {
    if (qL <= L && R <= qR)
        return root->sum +
               (add + root->add) * (R - L + 1);  //所有标记 * 区间长度
    int mid = (L + R) >> 1;
    LL res = 0;
    if (qL <= mid) res += query(Lson, L, mid, qL, qR, add + root->add);
    if (qR > mid) res += query(Rson, mid + 1, R, qL, qR, add + root->add);
    return res;
}
int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; i++) arr[i] = read();
    build(1, n, newNode(rt[0]));
    char opt;
    int l, r, d, t;
    while (m--) {
        cin >> opt;
        if (opt == 'C') {
            l = read(), r = read(), d = read();
            modify(rt[T], newNode(rt[T + 1]), 1, n, l, r, d);
            T++;
            continue;
        }
        if (opt == 'Q') {
            l = read(), r = read();
            printf("%lld\n", query(rt[T], 1, n, l, r, 0));
            continue;
        }
        if (opt == 'H') {
            l = read(), r = read(), t = read();
            printf("%lld\n", query(rt[t], 1, n, l, r, 0));
            continue;
        }
        T = read();
    }
    return 0;
}
#include<bits/stdc++.h>
//https://shaun118294191.github.io/post/cf1070c-cloud-computing/
//cloud computing
//https://www.luogu.com.cn/problem/CF1070C
constexpr int MAXN = 1e6 + 6;
using namespace std;
template <typename T> inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}
struct node {
    int l, r, c, p;
    inline bool operator < (const node &other) const {
        return p < other.p;
    }
}tariff[MAXN];
using LL = long long;
struct segTree {
    segTree * lson, *rson;
    LL max, min, tag;
}Tree[MAXN << 1];
using Node = segTree *;
#define Lson root->lson
#define Rson root->rson
int n, m, tot;
LL k, res, curC, curP;
inline void update(Node root) {
    root->max = max(Lson->max, Rson->max);
    root->min = min(Lson->min, Rson->min);
}
inline void build(int L, int R, Node root) {
    if (L == R) return;
    int mid = (L + R) >> 1;
    Lson = &Tree[++tot], Rson = &Tree[++tot];
    build(L, mid, Lson), build(mid + 1 ,R, Rson);
}
inline void pushTag(int L, int R, Node root) {
    if (!root->tag) return;
    Lson->tag += root->tag, Rson->tag += root->tag;
    Lson->max += root->tag, Rson->max += root->tag;
    Lson->min += root->tag, Rson->min += root->tag;
    root->tag = 0;
}
inline void change(int qL, int qR, int L, int R, Node root) {
    if (qL <= L && R <= qR) {
        if (root->min >= k) return;
        if (root->max + curC <= k) {
            root->max += curC, root->min += curC, root->tag += curC;
            res += curC * curP * (R - L + 1);
            return;
        } else if (root->max == root->min){
            LL delta = min(curC, k - root->max);
            root->max += delta, root->min += delta, root->tag += delta;
            res += delta * curP * (R - L + 1);
            return;
        }
        if (L == R) return;
    }
    pushTag(L, R, root);
    int mid = (L + R) >> 1;
    if (qL <= mid) change(qL, qR, L, mid, Lson);
    if (qR > mid) change(qL, qR, mid + 1, R, Rson);
    update(root);
}
int main() {
    freopen("test.in", "r", stdin);
    read(n), read(k), read(m);
    for (int i = 1; i <= m; i++) {
        read(tariff[i].l), read(tariff[i].r);
        read(tariff[i].c), read(tariff[i].p);
    }
    sort(tariff + 1, tariff + m + 1);
    build(1, n, Tree);
    for (int i = 1; i <= m; i++) {
        curC = tariff[i].c, curP = tariff[i].p;
        int l = tariff[i].l, r = tariff[i].r;
        change(l, r, 1, n, Tree);
    }
    cout << res << endl;
    return 0;
}
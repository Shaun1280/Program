#include <bits/stdc++.h>
constexpr int MAXN = 2e5 + 5;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
struct Scanline {
    int y, l, r, tag;
    Scanline() {}
    Scanline(int _y, int _l, int _r, int _tag)
        : y(_y), l(_l), r(_r), tag(_tag) {}
    inline friend bool operator<(const Scanline &a, const Scanline &b) {
        return a.y < b.y;
    }
};
vector<Scanline> vec;
struct Node {
    Node *lson, *rson;
    int l, r, cnt, len;
} Tree[MAXN << 2];
long long n, sum, tot, cnt;
vector<int> num;
map<int, int> Map;
inline void discretizaton() {
    sort(num.begin(), num.end());
    cnt = unique(num.begin(), num.end()) - num.begin();
    for (int i = 0; i < cnt; i++) Map[num[i]] = i;
}
inline void update(Node *root) {
    if (root->cnt)
        root->len = num[root->r + 1] - num[root->l];
    else
        root->len = (root->lson == nullptr ? 0 : root->lson->len) +
                    (root->rson == nullptr ? 0 : root->rson->len);
}
inline void build(int L, int R, Node *root) {
    root->l = L, root->r = R;
    if (L == R) return;
    int mid = (L + R) >> 1;
    root->lson = &Tree[++tot], root->rson = &Tree[++tot];
    build(L, mid, root->lson), build(mid + 1, R, root->rson);
}
inline void change(int L, int R, int tag, Node *root) {
    if (root->l == L && root->r == R) {
        root->cnt += tag;
        update(root);
        return;
    }
    int mid = (root->l + root->r) >> 1;
    if (R <= mid)
        change(L, R, tag, root->lson);
    else if (L > mid)
        change(L, R, tag, root->rson);
    else
        change(L, mid, tag, root->lson), change(mid + 1, R, tag, root->rson);
    update(root);
}
int main() {
    n = read();
    for (int i = 0, x, y, x2, y2; i < n; i++) {
        x = read(), y = read(), x2 = read(), y2 = read();
        vec.push_back(Scanline(y, x, x2, 1)),
            vec.push_back(Scanline(y2, x, x2, -1));
        num.push_back(x), num.push_back(x2);
    }
    discretizaton();
    build(0, cnt - 1, Tree);
    sort(vec.begin(), vec.end());
    for (int i = 0; i + 1 < vec.size(); i++) {
        int l = vec[i].l, r = vec[i].r, tag = vec[i].tag;
        change(Map[l], Map[r] - 1, tag, Tree);
        sum += 1LL * (Tree->len) * (vec[i + 1].y - vec[i].y);
    }
    cout << sum << endl;
    return 0;
}
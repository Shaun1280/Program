#include <bits/stdc++.h>
// https://shaun118294191.github.io/post/cf1320c-world-of-darkraft-battle-for-azathoth/
// CF1320C World of Darkraft: Battle for Azathoth
constexpr int MAXN = 2e5 + 5;
constexpr int Inf = 0x7fffffff;

using namespace std;
using LL = long long;

template <typename T>
inline void read(T &x) {
    int f = 1;
    x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct segTree {
    segTree *Lson, *Rson;
    int l, r;
    int max, tag;
} Tree[MAXN << 1];
int tot, n, m, p, ans = -Inf;
vector<pair<int, int> > weapon, armor;
vector<pair<int, pair<int, int> > > vec;
using Node = segTree *;

#define Lson root->Lson
#define Rson root->Rson
inline void build(int L, int R, Node root) {
    root->l = L, root->r = R;
    if (L == R) {
        root->max = -armor[L].second;
        return;
    }
    int mid = (L + R) >> 1;
    Lson = &Tree[++tot], Rson = &Tree[++tot];
    build(L, mid, Lson), build(mid + 1, R, Rson);
    root->max = max(Lson->max, Rson->max);
}

inline void pushTag(Node root) {
    if (!root->tag) return;
    Lson->tag += root->tag, Lson->max += root->tag;
    Rson->tag += root->tag, Rson->max += root->tag;
    root->tag = 0;
}

inline void change(int L, int R, int val, Node root) {
    if (L <= root->l && root->r <= R) {
        root->max += val, root->tag += val;
        return;
    }
    pushTag(root);
    int mid = (root->l + root->r) >> 1;
    if (L <= mid) change(L, R, val, Lson);
    if (R > mid) change(L, R, val, Rson);
    root->max = max(Lson->max, Rson->max);
}

int main() {
    read(n), read(m), read(p);
    for (int i = 0, v, c; i < n; i++)  //武器与怪物防御力放在一起排序
        read(v), read(c), vec.emplace_back(make_pair(v - 1, make_pair(Inf, c)));
    for (int i = 0, v, c; i < m; i++)
        read(v), read(c), armor.emplace_back(make_pair(v, c));
    sort(armor.begin(), armor.end());  //防具按防御值升序排序
    build(0, m - 1, Tree);             //按防具下标建树
    for (int i = 0, def, atk, c; i < p; i++) {
        read(def), read(atk), read(c);
        vec.emplace_back(make_pair(def, make_pair(atk, c)));
    }
    sort(vec.begin(), vec.end());
    for (auto &i : vec) {
        int x = i.first, y = i.second.first, c = i.second.second;
        if (y == Inf) {  // y = inf表明这是一个武器
            ans = max(ans, -c + Tree->max);
            continue;
        }
        int pos = upper_bound(armor.begin(), armor.end(), make_pair(y, Inf)) -
                  armor.begin();
        if (pos < m) change(pos, m - 1, c, Tree);  //后缀区间增值
    }
    cout << ans << endl;
    return 0;
}
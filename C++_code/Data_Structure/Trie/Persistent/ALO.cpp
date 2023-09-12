#include <bits/stdc++.h>
//https://www.luogu.com.cn/problem/P4098
//https://shaun-shane.vercel.app/2020/07/12/ALO/
constexpr int MAXN = 5e4 + 4;
constexpr int BIT = 30;

using namespace std;

template <typename T>
inline void read(T &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x *= f;
}

struct node {
    int key, pos;
    inline bool operator < (const node &other) const {
        return pos < other.pos;
    }
}jewel[MAXN];

inline bool cmp(const node &a, const node &b) {
    return a.key > b.key;
}

struct Trie {
    Trie *son[2];
    int lst;
}Tree[MAXN << 5], *root[MAXN];
using Node = Trie *;

inline Node newNode(Node &root) {
    static int nptr;
    return root = &Tree[++nptr];
}

inline void insert(Node pre, Node root, int x, int index) {
    for (int i = BIT - 1; ~i; i--) {
        int tmp = (x >> i) & 1;
        if (pre) root->son[tmp ^ 1] = pre->son[tmp ^ 1];
        root->lst = max(root->lst, index);
        root = newNode(root->son[tmp]), pre = pre ? pre->son[tmp] : NULL;
    }
    root->lst = max(root->lst, index);
}

inline int search(Node root, int x, int limit) {
    int res = 0;
    for (int i = BIT - 1; ~i; i--) {
        int tmp = (x >> i) & 1;
        if (root->son[tmp ^ 1] && root->son[tmp ^ 1]->lst >= limit)
            res |= (1 << i), root = root->son[tmp ^ 1];
        else root = root->son[tmp];
    }
    return res;
}

int main() {
    int n, res(0);
    set<node> s;
    set<node>::iterator l, r;
    read(n);
    insert(Tree, newNode(root[0]), 0, 0);
    for (int i = 1; i <= n; i++) {
        read(jewel[i].key), jewel[i].pos = i;
        insert(root[i - 1], newNode(root[i]), jewel[i].key, i);
    }
    sort(jewel + 1, jewel + n + 1, cmp); //按key值从大到小插入元素
    s.insert(jewel[1]); //按key值从大到小插入元素
    for (int i = 2, L, R; i <= n; i++) {
        l = r = s.lower_bound(jewel[i]); //求后继(后继已插入 按indices查找)

        if (l != s.begin()) --l;
        if (l != s.begin()) --l, L = l->pos + 1;
        else L = 1;

        if (r != s.end()) ++r;
        if (r != s.end()) R = r->pos - 1;
        else R = n;

        res = max(res, search(root[R], jewel[i].key, L));
        s.insert(jewel[i]);
    }
    cout << res << endl;
    return 0;
}